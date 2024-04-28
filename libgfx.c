/***********************************************************
	         mini-library 2016-02
	            Edouard  BERGE

      !!! DO NOT INCLUDE THIS FILE, USE library.h !!!	

changes v013:
- new libpng support with indirect access to struct
- bugfix ImageFillSurface (no more call to ImageFillSurface32)

changes v012:
- PNGRead improvements (handle palette and gray PNG)
- PNGRead alpha inversion makes v012 not compatible with previous versions

changes v011:
- ImageRAWHeaderInfo
- ImageRAWInfo
- ImageRAWRead
- ImageRAWWrite

changes v010:
- ImageMapToBox32
- ImageMapToBox(32) resized in Y destination
- ImageResize(32) is using fully accurate sub-pixels with bi-cubic clipping
- ImageReduction(32) is now an alias for ImageResize(32)
- ImageCrop(32) is now an alias for ImageCanvasSize(32)
- Clean up
- ImageRGBAToRGB,ImageFreeRGBAToRGB
- PNGRead24
- ImageInsertSprite(32)

changes v009:
- ImageFillSurface(32)
- ImageResize(32)
- bugfix in ImageReduction(32)
- better precision in ImageReduction(32)
- ImageRGBToRGBA,ImageFreeRGBToRGBA
- ImageCrop(32), ImageCanvasSize(32)
- PNGRead32

changes v008:
- SimplexNoise1D, SimplexNoise2D

changes v007:
- PNGRead can handle RGBA png

changes v006:
- ImageCrop, ImageMapToBox, ImageRGBToBW
- bugfix in ImageReduction

changes v005:
- PNGInitTrueColor
- ImageReduction32X2H, ImageReduction32X2W, ImageReduction32X2, ImageReduction32
  (optimised versions for 32 bits display)

changes v004:
- ImageReduction

changes v003:
- PNGInit, PNGRead, PNGWrite, PNGFree
- Thread mini-library
- ImageSmoothGaussian5x5 is now multi-threaded
- Bugfix in AutoLevel
- ImageReductionX2H, ImageReductionX2W (both multi-threaded)

changes v002:
- ImageReductionX2 (multi-threaded)

initial release v001:
- ImageCalcHistoR, ImageCalcHistoG, ImageCalcHistoB
- ImageRGBToCRB, ImageCRBToRGB
- ImageSmooth, ImageSmoothGaussian5x5
- ImageGradient
- ImageSharpness, ImageWideSharpness
- ImageContrast, ImageAutoLevel


************************************************************/

#define __FILENAME__ "libgfx_v012.c"

#define LIBGFX_LINK " -lpng16"
/*
	Vector structures
*/

#include"png.h"

#ifndef Z_DEFAULT_COMPRESSION
#define Z_DEFAULT_COMPRESSION 7
#endif

typedef int   v4si __attribute__ ((vector_size (4*sizeof(int))));
typedef int   v4ui __attribute__ ((vector_size (4*sizeof(unsigned short int))));
typedef float v4df __attribute__ ((vector_size (4*sizeof(float))));

union i4vector
{
        v4si v;
        int i[4];
};

union u4vector
{
        v4ui v;
        unsigned short int i[4];
};

union f4vector
{
        v4df v;
        float f[4];
};

/*
	Thread management functions
*/

struct s_image_thread {
	pthread_t thread;
	unsigned char *pixels;
	unsigned char *pixels2;
	unsigned char *newpix;
	int width,height;
	int param,param2;
};

void _internal_ImageFreeThreadStruct(int nb_cores, struct s_image_thread *image_threads, int free_submem)
{
	#undef FUNC
	#define FUNC "_internal_ImageFreeThreadStruct"

	int i;

	if (free_submem) {
	 	for (i=0;i<nb_cores;i++) {
			MemFree(image_threads[i].newpix);
		}
	}
	MemFree(image_threads);
}

void _internal_ImageExecuteThreads(int nb_cores, struct s_image_thread *image_threads, void *(*fct)(void *), int (*gfx_thread_prepare)(struct s_image_thread *,int,int))
{
	#undef FUNC
	#define FUNC "_internal_ImageExecuteThreads"

	pthread_attr_t attr;
	void *status;
	int i,rc;
	/* launch threads */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	pthread_attr_setstacksize(&attr,65536);

 	for (i=0;i<nb_cores;i++) {
		if (*gfx_thread_prepare)
			gfx_thread_prepare(image_threads,i,nb_cores);

		if ((rc=pthread_create(&image_threads[i].thread,&attr,fct,(void *)&image_threads[i]))) {
			logerr("Cannot create thread!");
			exit(INTERNAL_ERROR);
		}
	}
 	for (i=0;i<nb_cores;i++) {
		if ((rc=pthread_join(image_threads[i].thread,&status))) {
			logerr("thread error!");
			exit(INTERNAL_ERROR);
		}
	}
}

struct s_image_thread *_internal_MultiImageSplitForThreads(unsigned char *pixels, unsigned char *pixels2, int width, int height, int *nb_cores)
{
	#undef FUNC
	#define FUNC "_internal_ImageSplitForThread"

	struct s_image_thread *image_threads;
	int i,cury,prevy,step;

	/* sometimes we do not want to split the work into the exact number of cores */
	if (!*nb_cores) {
		*nb_cores=_internal_CPUGetCoreNumber();
	}
	image_threads=MemCalloc(sizeof(struct s_image_thread)*(*nb_cores));

	/* we want an even step */
	step=(height/(*nb_cores)) & 0x7FFFFFFE;

	/* do not thread too small parts */
	while (step<8 && *nb_cores>1) {
		*nb_cores=*nb_cores>>1;
		step=(height/(*nb_cores)) & 0x7FFFFFFE;
	}

	/* split image into strips */
	for (prevy=cury=i=0;i<*nb_cores-1;i++) {
		cury+=step;
		image_threads[i].pixels=pixels+prevy*width*3;
		image_threads[i].pixels2=pixels2+prevy*width*3;
		image_threads[i].height=cury-prevy;
		image_threads[i].width=width;
		prevy=cury;
	}
	image_threads[i].pixels=pixels+prevy*width*3;
	image_threads[i].pixels2=pixels2+prevy*width*3;
	image_threads[i].height=height-prevy;
	image_threads[i].width=width;

	return image_threads;
}
#define _internal_ImageSplitForThreads(pixels,width,height,nb_cores) _internal_MultiImageSplitForThreads(pixels, NULL, width, height, nb_cores)
#define _internal_ImageSplitForThreads2(pixels,pixels2,width,height,nb_cores) _internal_MultiImageSplitForThreads(pixels, pixels2, width, height, nb_cores)



unsigned int * _internal_ImageCalcHistoOneChannel(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "_internal_ImageCalcHistoOneChannel"

	unsigned int *histo;
	unsigned int i,max=0;
	unsigned int idx;

	histo=MemMalloc(257*sizeof(int));
	memset(histo,0,257*sizeof(int));
	for (i=0;i<width*height*3;i+=3) {
		idx=pixels[i];
		histo[idx]++;
		
		if (idx && idx<255 && histo[idx]>max) max=histo[idx];
	}
	histo[256]=max;
	return histo;
}
unsigned int * ImageCalcHistoR(unsigned char *pixels, int width, int height)
{
	return _internal_ImageCalcHistoOneChannel(pixels,width,height);
}
unsigned int * ImageCalcHistoG(unsigned char *pixels, int width, int height)
{
	return _internal_ImageCalcHistoOneChannel(pixels+1,width,height);
}
unsigned int * ImageCalcHistoB(unsigned char *pixels, int width, int height)
{
	return _internal_ImageCalcHistoOneChannel(pixels+2,width,height);
}

/***
	ImageRGBToCRB
*/
unsigned char * ImageRGBToCRB(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageRGBToCRB"

        unsigned char *newpix;;
        int i;
        double r,g,b;

        newpix=MemMalloc(width*height*3);

        for (i=0;i<width*height*3;i+=3) {
                r=pixels[i+0];
                g=pixels[i+1];
                b=pixels[i+2];
                newpix[i+0]=MinMaxInt(0.257*r+0.504*g+0.098*b+16,0,255);
                newpix[i+1]=MinMaxInt(-0.148*r-0.291*g+0.439*b+128,0,255);
                newpix[i+2]=MinMaxInt(0.439*r-0.368*g-0.071*b+128,0,255);
        }
        return newpix;
}

unsigned char *ImageRRGGBBToRRGGBBAA(unsigned char *data, int sizex,int sizey)
{
	#undef FUNC
	#define FUNC "ImageRRGGBBToRRGGBBAA"

	unsigned char *newdata;
	int i,ptr=0;

	if (!data) return NULL;
	if (sizex<=0 || sizey<=0) return NULL;

	newdata=MemMalloc(sizex*sizey*8);

	for (i=0;i<sizex*sizey*6;i+=6) {
		newdata[ptr++]=data[i];
		newdata[ptr++]=data[i+1];
		newdata[ptr++]=data[i+2];
		newdata[ptr++]=data[i+3];
		newdata[ptr++]=data[i+4];
		newdata[ptr++]=data[i+5];
		newdata[ptr++]=0;
		newdata[ptr++]=0;
	}
	return newdata;
}
unsigned char *ImageFreeRRGGBBToRRGGBBAA(unsigned char *data, int sizex,int sizey)
{
	#undef FUNC
	#define FUNC "ImageFreeRRGGBBToRRGGBBAA"

	unsigned char *newdata;

	if (!data) return NULL;

	newdata=ImageRRGGBBToRRGGBBAA(data,sizex,sizey);
	MemFree(data);
	return newdata;
}

unsigned char *ImageRGBToRGBA(unsigned char *data, int sizex,int sizey)
{
	#undef FUNC
	#define FUNC "ImageRGBToRGBA"

	unsigned char *newdata;
	int i,ptr=0;

	if (!data) return NULL;
	if (sizex<=0 || sizey<=0) return NULL;

	newdata=MemMalloc(sizex*sizey*4);

	for (i=0;i<sizex*sizey*3;i+=3) {
		newdata[ptr++]=data[i];
		newdata[ptr++]=data[i+1];
		newdata[ptr++]=data[i+2];
		newdata[ptr++]=255;
	}
	return newdata;
}
unsigned char *ImageFreeRGBToRGBA(unsigned char *data, int sizex,int sizey)
{
	#undef FUNC
	#define FUNC "ImageRGBToRGBA"

	unsigned char *newdata;

	if (!data) return NULL;

	newdata=ImageRGBToRGBA(data,sizex,sizey);
	MemFree(data);
	return newdata;
}

unsigned char *ImageRGBAToRGB(unsigned char *data, int sizex,int sizey)
{
	#undef FUNC
	#define FUNC "ImageRGBAToRGB"

	unsigned char *newdata;
	int i,ptr=0;

	if (!data) return NULL;
	if (sizex<=0 || sizey<=0) return NULL;

	newdata=MemMalloc(sizex*sizey*3);

	for (i=0;i<sizex*sizey*4;i+=4) {
		newdata[ptr++]=data[i];
		newdata[ptr++]=data[i+1];
		newdata[ptr++]=data[i+2];
	}
	return newdata;
}
unsigned char *ImageFreeRGBAToRGB(unsigned char *data, int sizex,int sizey)
{
	#undef FUNC
	#define FUNC "ImageRGBAToRGB"

	unsigned char *newdata;

	if (!data) return NULL;

	newdata=ImageRGBAToRGB(data,sizex,sizey);
	MemFree(data);
	return newdata;
}


unsigned char * ImageCRBToRGB(unsigned char *crb, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageCRBToRGB"

        unsigned char *newpix;;
        double y;
        int i,u,v;

        newpix=MemMalloc(width*height*3);

        for (i=0;i<width*height*3;i+=3) {
                /*
                        R = Y + 1,13983⋅V
                        G = Y − 0,39465⋅U − 0,58060⋅V
                        B = Y + 2,03211⋅U
                */
                y=(crb[i+0]-16)*1.164;
                u=crb[i+1]-128;
                v=crb[i+2]-128;
                newpix[i+0]=MinMaxInt(y+1.596*v,0,255);
                newpix[i+1]=MinMaxInt(y-0.813*v-0.391*u,0,255);
                newpix[i+2]=MinMaxInt(y+2.018*u,0,255);

        }
        return newpix;
}

unsigned char *ImageRGBToBW(unsigned char *pixels, int width, int height)
{
	#undef FUNC
	#define FUNC "ImageRGBToBW"

	unsigned char *newpix;
	int i;

	newpix=MemMalloc(width*height*3);

	for (i=0;i<width*height;i++) {
		newpix[i*3+0]=newpix[i*3+1]=newpix[i*3+2]=(pixels[i*3+0]*76+pixels[i*3+1]*153+pixels[i*3+2]*25)/256;
	}
	return newpix;
}

unsigned char * ImageSmooth(unsigned char *wrkpix, int width, int height, int force)
{
        #undef FUNC
	#define FUNC "ImageSmooth"

	unsigned char *newpix;
	int x,y,t,l;

        newpix=MemMalloc(width*height*3);
	for (x=3;x<width*3-3;x++) {
		t =wrkpix[x]*5;
		t+=wrkpix[x+3];
		t+=wrkpix[x-3];
		t+=wrkpix[x+width*3];
		newpix[x]=t/8;
	}
        for (y=1;y<height-1;y++)
        {
                l=y*width*3;
                for (x=3;x<width*3-3;x++) {
			t =wrkpix[l+x]*4;
                        t+=wrkpix[l+x+3];
                        t+=wrkpix[l+x-3];
                        t+=wrkpix[l+x-width*3];
                        t+=wrkpix[l+x+width*3];
                        newpix[l+x]=t/8;
		}
	}
	l=(height-1)*width*3;
	for (x=3;x<width*3-3;x++) {
		t =wrkpix[l+x]*5;
		t+=wrkpix[l+x+3];
		t+=wrkpix[l+x-3];
		t+=wrkpix[l+x-width*3];
		newpix[l+x]=t/8;
	}
	newpix[0]=wrkpix[0]; newpix[1]=wrkpix[1]; newpix[2]=wrkpix[2];
	newpix[(width-1)*3]=wrkpix[(width-1)*3]; newpix[(width-1)*3+1]=wrkpix[(width-1)*3+1]; newpix[(width-1)*3+2]=wrkpix[(width-1)*3+2];
	newpix[0+l]=wrkpix[0+l]; newpix[1+l]=wrkpix[1+l]; newpix[2+l]=wrkpix[2+l];
	newpix[(width-1)*3+l]=wrkpix[(width-1)*3+l]; newpix[(width-1)*3+1+l]=wrkpix[(width-1)*3+1+l]; newpix[(width-1)*3+2+l]=wrkpix[(width-1)*3+2+l];

	return newpix;
}

#define GFX_GAUSSIAN_COMPUTE_NO_BORDER 0
#define GFX_GAUSSIAN_COMPUTE_UP_BORDER 1
#define GFX_GAUSSIAN_COMPUTE_DW_BORDER 2
#define GFX_GAUSSIAN_COMPUTE_BORDERS   3

unsigned char * _internal_ImageSmoothGaussian5x5(unsigned char *newpix, unsigned char *wrkpix, int width, int height,int compute_border)
{
        #undef FUNC
        #define FUNC "_internal_ImageSmoothGaussian5x5"

        int x,y,l,ly,lx,sx,sy,ssx,ssy,sex,sey,pix,mat,flag,cx;

	unsigned int gaussian_matrix[25]={ 2,4,5,4,2, 4,9,12,9,4, 5,12,15,12,5, 4,9,12,9,4, 2,4,5,4,2 };
	unsigned int gaussian_matrix_opt[15]={ 2,4,5, 4,9,12, 5,12,15, 4,9,12, 2,4,5 };
	unsigned int tr,tg,tb,s,max;
	float muldiv[160];
	int posy[4],iposy=0,posx[4],ix,iy;
	int addy;

	if (!newpix) newpix=MemMalloc(3*width*height);

	/* too small to do it */	
	if (width<4 || height<4) {
		memcpy(newpix,wrkpix,width*height*3);
		return newpix;
	}

	/* petit précalcul */
	for (x=1;x<160;x++) muldiv[x]=1.0/x;
	addy=width*3;

        /* do the gaussian blur on the upper and lower borders */
	if (compute_border & GFX_GAUSSIAN_COMPUTE_UP_BORDER) {
		posy[iposy++]=0;
		posy[iposy++]=1;
	}
	if (compute_border & GFX_GAUSSIAN_COMPUTE_DW_BORDER) {
		posy[iposy++]=height-2;
		posy[iposy++]=height-1;
	}
	for (iy=0;iy<iposy;iy++)
        {
		y=posy[iy];
                l=y*width*3;
                for (x=0;x<width;x++) {
			tr=tg=tb=s=0;
			ssx=-2;sex=2;if (x==0) ssx=0; else if (x==1) ssx=-1; else if (x==width-2) sex=1; else if (x==width-1) sex=0;
			ssy=-2;sey=2;if (y==0) ssy=0; else if (y==1) ssy=-1; else if (y==height-2) sey=1; else if (y==height-1) sey=0;
			for (sy=ssy;sy<=sey;sy++) for (sx=ssx;sx<=sex;sx++) {
				pix=l+(x+sx+sy*width)*3;
				mat=gaussian_matrix[sx+2+(sy+2)*5];
				s+=mat;
				tr+=wrkpix[pix]*mat;
				tg+=wrkpix[pix+1]*mat;
				tb+=wrkpix[pix+2]*mat;
			}
			newpix[l+x*3+0]=tr*muldiv[s];
			newpix[l+x*3+1]=tg*muldiv[s];
			newpix[l+x*3+2]=tb*muldiv[s];
                }
        }
	/* prepare index for left and right borders */
	posx[0]=0;
	posx[1]=1;
	posx[2]=width-2;
	posx[3]=width-1;
	/* optimised loop on the main pixels */
	for (y=2;y<height-2;y++)
        {
                l=y*width*3;
		/* do the gaussian blur on the left and right borders */
                for (ix=0;ix<4;ix++) {
			x=posx[ix];
			tr=tg=tb=s=0;
			ssx=-2;sex=2;if (x==0) ssx=0; else if (x==1) ssx=-1; else if (x==width-2) sex=1; else if (x==width-1) sex=0;
			ssy=-2;sey=2;if (y==0) ssy=0; else if (y==1) ssy=-1; else if (y==height-2) sey=1; else if (y==height-1) sey=0;
			for (sy=ssy;sy<=sey;sy++) for (sx=ssx;sx<=sex;sx++) {
				pix=l+(x+sx+sy*width)*3;
				mat=gaussian_matrix[sx+2+(sy+2)*5];
				s+=mat;
				tr+=wrkpix[pix]*mat;
				tg+=wrkpix[pix+1]*mat;
				tb+=wrkpix[pix+2]*mat;
			}
			newpix[l+x*3+0]=tr*muldiv[s];
			newpix[l+x*3+1]=tg*muldiv[s];
			newpix[l+x*3+2]=tb*muldiv[s];
                }
		/* optimised loop for the main pixels when no clipping is needed */
		ly=l+(-2*width)*3;
		for (x=2;x<width-2;x++) {
			cx=tr=tg=tb=0;
			pix=ly;
			sy=5;
			while (sy) {
				mat=gaussian_matrix_opt[cx];
				tr+=wrkpix[pix]*mat;
				tg+=wrkpix[pix+1]*mat;
				tb+=wrkpix[pix+2]*mat;

				mat=gaussian_matrix_opt[cx+1];
				tr+=wrkpix[pix+3]*mat;
				tg+=wrkpix[pix+4]*mat;
				tb+=wrkpix[pix+5]*mat;

				mat=gaussian_matrix_opt[cx+2];
				tr+=wrkpix[pix+6]*mat;
				tg+=wrkpix[pix+7]*mat;
				tb+=wrkpix[pix+8]*mat;

				mat=gaussian_matrix_opt[cx+1];
				tr+=wrkpix[pix+9]*mat;
				tg+=wrkpix[pix+10]*mat;
				tb+=wrkpix[pix+11]*mat;

				mat=gaussian_matrix_opt[cx];
				tr+=wrkpix[pix+12]*mat;
				tg+=wrkpix[pix+13]*mat;
				tb+=wrkpix[pix+14]*mat;

				pix+=addy;
				cx+=3;
				sy--;
			}
			/* matrice complète, coef de 159 */
			newpix[l+x*3+0]=tr*0.006289308;
			newpix[l+x*3+1]=tg*0.006289308;
			newpix[l+x*3+2]=tb*0.006289308;
			ly+=3;
                }
        }
        return newpix;
}

void *_internal_ImageSmoothGaussian5x5Thread(void *p_image_thread)
{
        #undef FUNC
        #define FUNC "_internal_ImageSmoothGaussian5x5Thread"

	struct s_image_thread *image_thread;

	image_thread=(struct s_image_thread *)p_image_thread;
	_internal_ImageSmoothGaussian5x5(image_thread->newpix,image_thread->pixels, image_thread->width, image_thread->height, image_thread->param);

	pthread_exit(NULL);
}
int _internal_ImageSmoothGaussian5x5ThreadPrepare(struct s_image_thread *image_threads,int idx, int nb_cores)
{
        #undef FUNC
        #define FUNC "_internal_ImageSmoothGaussian5x5ThreadBorder"

	static int cury=0;

	if (idx==0) {
		image_threads[0].param=GFX_GAUSSIAN_COMPUTE_UP_BORDER;
		cury=image_threads[0].height;
		return 1;
	}

	if (idx==nb_cores-1) {
		image_threads[idx].param=GFX_GAUSSIAN_COMPUTE_DW_BORDER;
	} else {
		image_threads[idx].param=GFX_GAUSSIAN_COMPUTE_NO_BORDER;
	}
	
	image_threads[idx].newpix=image_threads[0].newpix+cury*image_threads[idx].width*3;
	cury+=image_threads[idx].height;

	return 1;
}

unsigned char * ImageSmoothGaussian5x5(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageSmoothGaussian5x5"

	struct s_image_thread *image_threads;
	struct s_image_thread *fusion_threads;
	unsigned char *newpix;
	int curheight,offset,cursize;
	int i,nb_cores=0,cury,prevy,step;

	image_threads=_internal_ImageSplitForThreads(pixels,width,height,&nb_cores);

	/* if the image is too small or if there is only one core, just do it simply */
	if (nb_cores==1 || height/nb_cores<=16) {
		_internal_ImageFreeThreadStruct(nb_cores,image_threads,0);
		return _internal_ImageSmoothGaussian5x5(NULL,pixels,width,height,GFX_GAUSSIAN_COMPUTE_BORDERS);
	}
	image_threads[0].newpix=MemMalloc(height*width*3);
	newpix=image_threads[0].newpix;

	_internal_ImageExecuteThreads(nb_cores,image_threads,_internal_ImageSmoothGaussian5x5Thread,_internal_ImageSmoothGaussian5x5ThreadPrepare);

	/* to be accurate, we need to compute the transitions between strips */
	fusion_threads=MemCalloc((nb_cores-1)*sizeof(struct s_image_thread));
	for (i=1;i<nb_cores;i++) {
		fusion_threads[i-1].pixels=image_threads[i].pixels-4*width*3;
		fusion_threads[i-1].width=width;
		fusion_threads[i-1].height=8;
		fusion_threads[i-1].param=GFX_GAUSSIAN_COMPUTE_NO_BORDER;
		fusion_threads[i-1].newpix=MemMalloc(width*8*3);
	}
	_internal_ImageExecuteThreads(nb_cores-1,fusion_threads,_internal_ImageSmoothGaussian5x5Thread,NULL);
	curheight=0;
	for (i=1;i<nb_cores;i++) {
		curheight+=image_threads[i-1].height;
		memcpy(newpix+(curheight-2)*width*3,fusion_threads[i-1].newpix+width*2*3,width*4*3);
	}

	/* free structs */
	_internal_ImageFreeThreadStruct(nb_cores,image_threads,0);
	_internal_ImageFreeThreadStruct(nb_cores-1,fusion_threads,1);

	return newpix;
}



unsigned char * ImageGradient(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageGradient"

        unsigned char *newpix;
        int x,y,l;

        newpix=MemCalloc(width*height*3);

        for (y=0;y<height;y++)
        {
                l=y*width*3;
                for (x=6;x<width*3-6;x++) {
			newpix[l+x]=abs(pixels[l+x+3]-pixels[l+x-3]);
		}
	}

        return newpix;
}

unsigned char * ImageSharpness(unsigned char *pixels, int width, int height, int force)
{
        #undef FUNC
        #define FUNC "ImageSharpness"

        unsigned char *newpix,*wrkpix;
        int x,y,t,l;

        newpix=MemMalloc(width*height*3);

        /* do the blur on the luminance */
        wrkpix=ImageRGBToCRB(pixels,width,height);
        for (y=1;y<height-1;y++)
        {
                l=y*width*3;
                for (x=1;x<width-1;x++) {
                        t =wrkpix[l+x*3+3];
                        t+=wrkpix[l+x*3-3];
                        t+=wrkpix[l+x*3-width*3];
                        t+=wrkpix[l+x*3+width*3];
                        newpix[l+x*3]=t/4;
                        newpix[l+x*3+1]=wrkpix[l+x*3+1];
                        newpix[l+x*3+2]=wrkpix[l+x*3+2];
                }
        }
        /* copy borders without modification */
        for (y=0;y<height;y++) {
                l=y*width*3;
                newpix[l+0]=wrkpix[l+0];
                newpix[l+0+width*3-3]=wrkpix[l+0+width*3-3];
        }
        l=(height-1)*width*3;
        for (x=0;x<width;x++) {
                newpix[x*3+0]=wrkpix[x*3+0];
                newpix[l+x*3+0]=wrkpix[l+x*3+0];
        }
        /* do the sharpness with the blur */
        for (x=0;x<width*height*3;x+=3) {
                wrkpix[x]=MinMaxInt(wrkpix[x]+(wrkpix[x]-newpix[x])*force*0.1,0,255);
        }
        /* then come back to RGB */
        MemFree(newpix);
        newpix=ImageCRBToRGB(wrkpix,width,height);
        MemFree(wrkpix);
        return newpix;
}
unsigned char * ImageWideSharpness(unsigned char *pixels, int width, int height, int force)
{
        #undef FUNC
        #define FUNC "ImageWideSharpness"

        unsigned char *newpix,*wrkpix;
        int x,y,l,sx,sy;

	unsigned int sharp_matrix[25]={ 0,2,4,2,0, 2,6,8,6,2, 4,8,88,8,4, 2,6,8,6,2, 0,2,4,2,0 };
	unsigned int t;

        newpix=MemCalloc(width*height*3);

        /* do the blur on the luminance */
        wrkpix=ImageRGBToCRB(pixels,width,height);
        for (y=2;y<height-2;y++)
        {
                l=y*width*3;
                for (x=2;x<width-2;x++) {
			t=0;
			for (sy=-2;sy<3;sy++) for (sx=-2;sx<3;sx++) {
				t+=wrkpix[l+x*3+sx*3+sy*width*3]*sharp_matrix[sx+2+(sy+2)*5];
			}
                        newpix[l+x*3]=t/176;
			/* chrominance ne change pas */
                        newpix[l+x*3+1]=wrkpix[l+x*3+1];
                        newpix[l+x*3+2]=wrkpix[l+x*3+2];
                }
        }
        /* do the sharpness with the blur */
        for (x=0;x<width*height*3;x+=3) {
                wrkpix[x]=MinMaxInt(wrkpix[x]+(wrkpix[x]-newpix[x])*force*0.1,0,255);
        }
        /* then come back to RGB */
        MemFree(newpix);
        newpix=ImageCRBToRGB(wrkpix,width,height);
        MemFree(wrkpix);
        return newpix;
}

unsigned char * ImageContrast(unsigned char *pixels, int width, int height, int force)
{
        #undef FUNC
        #define FUNC "ImageContrast"

        unsigned char tab_contrast[256];
        unsigned char *newpix;
        double contrast_step,curval,realval;
        int i;

        /* init values */
        contrast_step=1.0+force/100.0;
        curval=128-128*contrast_step;

        for (i=0;i<256;i++) {
                if (curval<0) realval=0; else if (curval>255) realval=255; else realval=curval;
                tab_contrast[i]=realval;
                curval+=contrast_step;
        }
        newpix=MemMalloc(width*height*3);

        /* apply contrast */
        for (i=0;i<width*height*3;i++) {
                newpix[i]=tab_contrast[pixels[i]];
        }
        return newpix;
}

unsigned char * ImageLevel(unsigned char *pixels, int width, int height, int lv, int hv)
{
        #undef FUNC
        #define FUNC "ImageLevel"

	unsigned char *newpix;
	unsigned char tab_level[256];
	double level_step,level_val;
	int i;

	newpix=MemMalloc(width*height*3);
	if (lv==0 && hv==255) {
		memcpy(newpix,pixels,width*height*3);
	} else {
		/* create conversion table */
		level_step=255.0/(double)(hv-lv);
		level_val=0;
		for (i=0;i<lv;i++) tab_level[i]=0;
		for (i=lv;i<=hv;i++) {
			tab_level[i]=MinMaxInt(level_val,0,255);
			level_val+=level_step;
		}
		for (i=hv;i<256;i++) tab_level[i]=255;
		/* level the picture */
		for (i=0;i<width*height*3;i++) {
			newpix[i]=tab_level[pixels[i]];
		}
	}
	return newpix;
}

unsigned char * ImageAutoLevel(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageAutoLevel"

	unsigned char *newpix;
	unsigned char tab_level[256];
	double level_step,level_val;
	int i,lv,hv;

	lv=255;
	hv=0;
	for (i=0;i<width*height*3;i++) {
		if (pixels[i]<lv) lv=pixels[i]; else
		if (pixels[i]>hv) hv=pixels[i];
	}
	newpix=MemMalloc(width*height*3);
	if (lv==0 && hv==255) {
		memcpy(newpix,pixels,width*height*3);
	} else {
		/* create conversion table */
		level_step=255.0/(double)(hv-lv);
		level_val=0;
		for (i=lv;i<=hv;i++) {
			tab_level[i]=MinMaxInt(level_val,0,255);
			level_val+=level_step;
		}
		/* level the picture */
		for (i=0;i<width*height*3;i++) {
			newpix[i]=tab_level[pixels[i]];
		}
	}
	return newpix;
}

/* réduction optimisée en 32 bits */

unsigned char * _internal_ImageReduction32X2H(unsigned char *newpix, unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2H"

	int newheight;
	int x,y,l,sl,hl,vy;

	newheight=height>>1;
	if (!newpix) newpix=MemMalloc(width*newheight*4);

	vy=0;
	for (y=0;y<newheight;y++) {
		sl=vy;
		l=vy*2;
		vy+=width*4;
		for (x=0;x<width;x++) {
			newpix[sl]=(pixels[l]+pixels[l+width*4])/2;
			newpix[sl+1]=(pixels[l+1]+pixels[l+width*4+1])/2;
			newpix[sl+2]=(pixels[l+2]+pixels[l+width*4+2])/2;
			newpix[sl+3]=(pixels[l+3]+pixels[l+width*4+3])/2;
			sl+=4;
			l+=4;
		}
	}
	return newpix;
}
unsigned char * _internal_ImageReduction32X2W(unsigned char *newpix, unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2W"

	int newwidth;
	int x,y,l,sl,hl,vy,vy2;

	newwidth=width>>1;
	if (!newpix) newpix=MemMalloc(newwidth*height*4);

	vy=vy2=0;
	for (y=0;y<height;y++) {
		sl=vy;
		l=vy2;
		vy+=width*4;
		vy2+=width*4*2;
		for (x=0;x<newwidth;x++) {
			newpix[sl]=(pixels[l]+pixels[l+4])/2;
			newpix[sl+1]=(pixels[l+1]+pixels[l+5])/2;
			newpix[sl+2]=(pixels[l+2]+pixels[l+6])/2;
			newpix[sl+3]=(pixels[l+3]+pixels[l+7])/2;
			sl+=4;
			l+=8;
		}
	}
	return newpix;
}
unsigned char * _internal_ImageReduction32X2(unsigned char *newpix, unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2"

	int newwidth,newheight;
	int x,y,l,sl,hl;

	newwidth=width>>1;
	newheight=height>>1;
	if (!newpix) newpix=MemMalloc(newwidth*newheight*4);

	for (y=0;y<newheight;y++) {
		sl=y*newwidth*4;
		l=y*2*width*4;
		for (x=0;x<newwidth*4;x+=4) {
			newpix[sl+x]=(pixels[l]+pixels[l+4]+pixels[l+width*4]+pixels[l+width*4+4])/4;
			newpix[sl+x+1]=(pixels[l+1]+pixels[l+5]+pixels[l+width*4+1]+pixels[l+width*4+5])/4;
			newpix[sl+x+2]=(pixels[l+2]+pixels[l+6]+pixels[l+width*4+2]+pixels[l+width*4+6])/4;
			newpix[sl+x+3]=(pixels[l+3]+pixels[l+7]+pixels[l+width*4+3]+pixels[l+width*4+7])/4;
			l+=8;
		}
	}
	return newpix;
}
void *_internal_ImageReduction32X2HThread(void *p_image_thread)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2HThread"

	struct s_image_thread *image_thread;

	image_thread=(struct s_image_thread *)p_image_thread;
	_internal_ImageReduction32X2H(image_thread->newpix,image_thread->pixels, image_thread->width, image_thread->height);

	pthread_exit(NULL);
}
void *_internal_ImageReduction32X2WThread(void *p_image_thread)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2WThread"

	struct s_image_thread *image_thread;

	image_thread=(struct s_image_thread *)p_image_thread;
	_internal_ImageReduction32X2W(image_thread->newpix,image_thread->pixels, image_thread->width, image_thread->height);

	pthread_exit(NULL);
}
void *_internal_ImageReduction32X2Thread(void *p_image_thread)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2Thread"

	struct s_image_thread *image_thread;

	image_thread=(struct s_image_thread *)p_image_thread;
	_internal_ImageReduction32X2(image_thread->newpix,image_thread->pixels, image_thread->width, image_thread->height);

	pthread_exit(NULL);
}
int _internal_ImageReduction32X2HThreadPrepare(struct s_image_thread *image_threads,int idx, int nb_cores)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2HThreadPrepare"

	static int cury=0;

	if (idx!=0) {
		image_threads[idx].newpix=image_threads[0].newpix+cury*image_threads[idx].width*4;
	} else {
		cury=0;
	}
	cury+=image_threads[idx].height>>1;

	return 1;
}
int _internal_ImageReduction32X2WThreadPrepare(struct s_image_thread *image_threads,int idx, int nb_cores)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2WThreadPrepare"

	static int cury=0;

	if (idx!=0) {
		image_threads[idx].newpix=image_threads[0].newpix+cury*(image_threads[idx].width>>1)*4;
	} else {
		cury=0;
	}
	cury+=image_threads[idx].height;

	return 1;
}
int _internal_ImageReduction32X2ThreadPrepare(struct s_image_thread *image_threads,int idx, int nb_cores)
{
        #undef FUNC
        #define FUNC "_internal_ImageReduction32X2ThreadPrepare"

	static int cury=0;

	if (idx!=0) {
		image_threads[idx].newpix=image_threads[0].newpix+cury*(image_threads[idx].width>>1)*4;
	} else {
		cury=0;
	}
	cury+=image_threads[idx].height>>1;

	return 1;
}
unsigned char * ImageReduction32X2H(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageReduction32X2H"

	struct s_image_thread *image_threads;
	unsigned char *newpix;
	int offset,cursize;
	int newheight,newwidth;
	int nb_cores=0;

	image_threads=_internal_ImageSplitForThreads(pixels,width,height,&nb_cores);
	newheight=height>>1;
	image_threads[0].newpix=newpix=MemMalloc(newheight*width*4);
	_internal_ImageExecuteThreads(nb_cores,image_threads,_internal_ImageReduction32X2Thread,_internal_ImageReduction32X2HThreadPrepare);

	/* free structs */
	_internal_ImageFreeThreadStruct(nb_cores,image_threads,0);

	return newpix;
}
unsigned char * ImageReduction32X2W(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageReduction32X2W"

	struct s_image_thread *image_threads;
	unsigned char *newpix;
	int offset,cursize;
	int newheight,newwidth;
	int nb_cores=0;

	image_threads=_internal_ImageSplitForThreads(pixels,width,height,&nb_cores);
	newwidth=width>>1;
	image_threads[0].newpix=newpix=MemMalloc(height*newwidth*4);
	_internal_ImageExecuteThreads(nb_cores,image_threads,_internal_ImageReduction32X2Thread,_internal_ImageReduction32X2WThreadPrepare);

	/* free structs */
	_internal_ImageFreeThreadStruct(nb_cores,image_threads,0);

	return newpix;
}
unsigned char * ImageReduction32X2(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageReduction32X2"

	struct s_image_thread *image_threads;
	unsigned char *newpix;
	int offset,cursize;
	int newheight,newwidth;
	int nb_cores=0;

	image_threads=_internal_ImageSplitForThreads(pixels,width,height,&nb_cores);
	newheight=height>>1;
	newwidth=width>>1;
	image_threads[0].newpix=newpix=MemMalloc(newheight*newwidth*4);
	_internal_ImageExecuteThreads(nb_cores,image_threads,_internal_ImageReduction32X2Thread,_internal_ImageReduction32X2ThreadPrepare);

	/* free structs */
	_internal_ImageFreeThreadStruct(nb_cores,image_threads,0);

	return newpix;
}

/* réduction originale en 24 bits */

unsigned char * _internal_ImageReductionX2H(unsigned char *newpix, unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2H"

	int newheight;
	int x,y,l,sl,hl,vy;

	newheight=height>>1;
	if (!newpix) newpix=MemMalloc(width*newheight*3);

	vy=0;
	for (y=0;y<newheight;y++) {
		sl=vy;
		l=vy*2;
		vy+=width*3;
		for (x=0;x<width*3;x+=3) {
			newpix[sl++]=(pixels[l]+pixels[l+width*3])/2;
			newpix[sl++]=(pixels[l+1]+pixels[l+width*3+1])/2;
			newpix[sl++]=(pixels[l+2]+pixels[l+width*3+2])/2;
			l+=3;
		}
	}
	return newpix;
}
unsigned char * _internal_ImageReductionX2W(unsigned char *newpix, unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2W"

	int newwidth;
	int x,y,l,sl,hl,vy,vy2;

	newwidth=width>>1;
	if (!newpix) newpix=MemMalloc(newwidth*height*3);

	vy=vy2=0;
	for (y=0;y<height;y++) {
		sl=vy;
		l=vy2;
		vy+=width*3;
		vy2+=width*3*2;
		for (x=0;x<newwidth*3;x+=3) {
			newpix[sl]=(pixels[l]+pixels[l+3])/2;
			newpix[sl+1]=(pixels[l+1]+pixels[l+4])/2;
			newpix[sl+2]=(pixels[l+2]+pixels[l+5])/2;
			sl+=3;
			l+=6;
		}
	}
	return newpix;
}
unsigned char * _internal_ImageReductionX2(unsigned char *newpix, unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2"

	int newwidth,newheight;
	int x,y,l,sl,hl;

	newwidth=width>>1;
	newheight=height>>1;
	if (!newpix) newpix=MemMalloc(newwidth*newheight*3);

	for (y=0;y<newheight;y++) {
		sl=y*newwidth*3;
		l=y*2*width*3;
		for (x=0;x<newwidth*3;x+=3) {
			newpix[sl+x]=(pixels[l]+pixels[l+3]+pixels[l+width*3]+pixels[l+width*3+3])/4;
			newpix[sl+x+1]=(pixels[l+1]+pixels[l+4]+pixels[l+width*3+1]+pixels[l+width*3+4])/4;
			newpix[sl+x+2]=(pixels[l+2]+pixels[l+5]+pixels[l+width*3+2]+pixels[l+width*3+5])/4;
			l+=6;
		}
	}
	return newpix;
}
void *_internal_ImageReductionX2HThread(void *p_image_thread)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2HThread"

	struct s_image_thread *image_thread;

	image_thread=(struct s_image_thread *)p_image_thread;
	_internal_ImageReductionX2H(image_thread->newpix,image_thread->pixels, image_thread->width, image_thread->height);

	pthread_exit(NULL);
}
void *_internal_ImageReductionX2WThread(void *p_image_thread)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2WThread"

	struct s_image_thread *image_thread;

	image_thread=(struct s_image_thread *)p_image_thread;
	_internal_ImageReductionX2W(image_thread->newpix,image_thread->pixels, image_thread->width, image_thread->height);

	pthread_exit(NULL);
}
void *_internal_ImageReductionX2Thread(void *p_image_thread)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2Thread"

	struct s_image_thread *image_thread;

	image_thread=(struct s_image_thread *)p_image_thread;
	_internal_ImageReductionX2(image_thread->newpix,image_thread->pixels, image_thread->width, image_thread->height);

	pthread_exit(NULL);
}
int _internal_ImageReductionX2HThreadPrepare(struct s_image_thread *image_threads,int idx, int nb_cores)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2HThreadPrepare"

	static int cury=0;

	if (idx!=0) {
		image_threads[idx].newpix=image_threads[0].newpix+cury*image_threads[idx].width*3;
	} else {
		cury=0;
	}
	cury+=image_threads[idx].height>>1;

	return 1;
}
int _internal_ImageReductionX2WThreadPrepare(struct s_image_thread *image_threads,int idx, int nb_cores)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2WThreadPrepare"

	static int cury=0;

	if (idx!=0) {
		image_threads[idx].newpix=image_threads[0].newpix+cury*(image_threads[idx].width>>1)*3;
	} else {
		cury=0;
	}
	cury+=image_threads[idx].height;

	return 1;
}
int _internal_ImageReductionX2ThreadPrepare(struct s_image_thread *image_threads,int idx, int nb_cores)
{
        #undef FUNC
        #define FUNC "_internal_ImageReductionX2ThreadPrepare"

	static int cury=0;

	if (idx!=0) {
		image_threads[idx].newpix=image_threads[0].newpix+cury*(image_threads[idx].width>>1)*3;
	} else {
		cury=0;
	}
	cury+=image_threads[idx].height>>1;

	return 1;
}
unsigned char * ImageReductionX2H(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageReductionX2H"

	struct s_image_thread *image_threads;
	unsigned char *newpix;
	int offset,cursize;
	int newheight,newwidth;
	int nb_cores=0;

	image_threads=_internal_ImageSplitForThreads(pixels,width,height,&nb_cores);
	newheight=height>>1;
	image_threads[0].newpix=newpix=MemMalloc(newheight*width*3);
	_internal_ImageExecuteThreads(nb_cores,image_threads,_internal_ImageReductionX2Thread,_internal_ImageReductionX2HThreadPrepare);

	/* free structs */
	_internal_ImageFreeThreadStruct(nb_cores,image_threads,0);

	return newpix;
}
unsigned char * ImageReductionX2W(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageReductionX2W"

	struct s_image_thread *image_threads;
	unsigned char *newpix;
	int offset,cursize;
	int newheight,newwidth;
	int nb_cores=0;

	image_threads=_internal_ImageSplitForThreads(pixels,width,height,&nb_cores);
	newwidth=width>>1;
	image_threads[0].newpix=newpix=MemMalloc(height*newwidth*3);
	_internal_ImageExecuteThreads(nb_cores,image_threads,_internal_ImageReductionX2Thread,_internal_ImageReductionX2WThreadPrepare);

	/* free structs */
	_internal_ImageFreeThreadStruct(nb_cores,image_threads,0);

	return newpix;
}
unsigned char * ImageReductionX2(unsigned char *pixels, int width, int height)
{
        #undef FUNC
        #define FUNC "ImageReductionX2"

	struct s_image_thread *image_threads;
	unsigned char *newpix;
	int offset,cursize;
	int newheight,newwidth;
	int nb_cores=0;

	image_threads=_internal_ImageSplitForThreads(pixels,width,height,&nb_cores);
	newheight=height>>1;
	newwidth=width>>1;
	image_threads[0].newpix=newpix=MemMalloc(newheight*newwidth*3);
	_internal_ImageExecuteThreads(nb_cores,image_threads,_internal_ImageReductionX2Thread,_internal_ImageReductionX2ThreadPrepare);

	/* free structs */
	_internal_ImageFreeThreadStruct(nb_cores,image_threads,0);

	return newpix;
}


unsigned char *ImageMapToBox(unsigned char *pixels, int width, int height, double startx, double starty, int w, int h, double vx1, double vy1) {
	#undef FUNC
	#define FUNC "ImageMapToBox"

	unsigned char *working_pixels,*box_pixels;
	double curx,cury,scanx,scany;
	double vx2,vy2,ovx1,ovy1;
	int x,y,depy;

	/* memory reserved for oversampling x4 */
	working_pixels=MemCalloc(w*h*3*16);
	/* compute normal vector */
	ovx1=vx1;
	ovy1=vy1;
	vx1=vx1/(double)w/4.0;
	vy1=vy1/(double)w/4.0;
	vx2=-ovy1/(double)h/4.0;
	vy2=ovx1/(double)h/4.0;

	w*=4;
	h*=4;
	/* do the mapping */
	depy=0;
	scanx=startx;scany=starty;
	for (y=0;y<h;y++) {
		curx=scanx;cury=scany;
		for (x=0;x<w;x++) {
			/* we must be inside the Img */
			if (curx>=0.0 && curx<width && cury>=0.0 && cury<height) {
				working_pixels[depy+x*3+0]=pixels[(int)(((int)curx+((int)cury)*width)*3+0)];
				working_pixels[depy+x*3+1]=pixels[(int)(((int)curx+((int)cury)*width)*3+1)];
				working_pixels[depy+x*3+2]=pixels[(int)(((int)curx+((int)cury)*width)*3+2)];
			}
			curx+=vx1;
			cury+=vy1;
		}
		scanx+=vx2;
		scany+=vy2;
		depy+=w*3;
	}

	/* resample */
	box_pixels=ImageReductionX2(working_pixels,w,h);
	MemFree(working_pixels);
	working_pixels=box_pixels;
	box_pixels=ImageReductionX2(working_pixels,w/2,h/2);
	MemFree(working_pixels);

	return box_pixels;
}
unsigned int *ImageMapToBox32(unsigned int *pixels, int width, int height, double startx, double starty, int w, int h, double vx1, double vy1) {
	#undef FUNC
	#define FUNC "ImageMapToBox32"

	unsigned int *working_pixels,*box_pixels;
	double curx,cury,scanx,scany;
	double vx2,vy2,ovx1,ovy1;
	int x,y,depy;

	/* memory reserved for oversampling x4 */
	working_pixels=MemCalloc(w*h*4*16);
	/* compute normal vector */
	ovx1=vx1;
	ovy1=vy1;
	vx1=vx1/(double)w/4.0;
	vy1=vy1/(double)w/4.0;
	vx2=-ovy1/(double)h/4.0;
	vy2=ovx1/(double)h/4.0;

	w*=4;
	h*=4;
	/* do the mapping */
	depy=0;
	scanx=startx;scany=starty;
	for (y=0;y<h;y++) {
		curx=scanx;cury=scany;
		for (x=0;x<w;x++) {
			/* we must be inside the Img */
			if (curx>=0.0 && curx<width && cury>=0.0 && cury<height) {
				working_pixels[depy+x]=pixels[(int)(((int)curx+((int)cury)*width))];
			}
			curx+=vx1;
			cury+=vy1;
		}
		scanx+=vx2;
		scany+=vy2;
		depy+=w;
	}

	/* resample */
	box_pixels=(unsigned int *)ImageReduction32X2((unsigned char *)working_pixels,w,h);
	MemFree(working_pixels);
	working_pixels=box_pixels;
	box_pixels=(unsigned int *)ImageReduction32X2((unsigned char*)working_pixels,w/2,h/2);
	MemFree(working_pixels);

	return box_pixels;
}

void _internal_ImageInsertSprite(unsigned char *pixels, int width, int height, unsigned char *sprite, int sw, int sh, int posx, int posy, int d)
{
	#undef FUNC
	#define FUNC "_internal_ImageInsertSprite"

	int x,y,p;
	int offset,idx=0,addidx=0,curoff;

	if (posx+sw<0) return;
	if (posx>=width) return;
	if (posy+sh<0) return;
	if (posy>=height) return;

	if (posy<0) {
		idx+=sw*d*-posy;
		sh+=posy;
		posy=0;
	}
	if (posx<0) {
		addidx+=-posx*d;
		sw+=posx;
		posx=0;
	}
	if (posx+sw>width) {
		addidx+=(posx+sw-width)*d;
		sw=width-posx;
	}
	if (posy+sh>=height) {
		sh=height-posy;
	}

	offset=(posx+posy*width)*d;

	for (y=0;y<sh;y++) {
		curoff=offset;
		idx+=addidx;
		for (x=0;x<sw;x++) {
			for (p=0;p<d;p++) {
				pixels[curoff++]=sprite[idx++];
			}
		}
		offset+=width*d;
	}
}
#define ImageInsertSprite(p,w,h,s,sw,sh,px,py) _internal_ImageInsertSprite(p,w,h,s,sw,sh,px,py,3)
#define ImageInsertSprite32(p,w,h,s,sw,sh,px,py) _internal_ImageInsertSprite(p,w,h,s,sw,sh,px,py,4)



#define CUBIC_BEZIER_COEF(c1) (c1*c1*(c1+3*(1.0-c1)))

unsigned char *ImageResize(unsigned char *pixels, int width, int height, int newwidth, int newheight)
{
	#undef FUNC
	#define FUNC "ImageResize"

	unsigned char *newpix;
	double tr,tv,tb;
	double curx,cury,vx,vy,fracx,fracy,pcount,coef1,coef2,fracxend,fracyend,coefy1,coefy2,coefx1,coefx2;
	int x,y,icurx,icury,dst=0,subx,suby,iendx,iendy;

	newpix=MemMalloc(newwidth*newheight*3);
	vx=(double)(width-1)/(double)newwidth;
	vy=(double)(height-1)/(double)newheight;

	if (vx<=1.0 && vy<=1.0) {
		cury=0.5;
		for (y=0;y<newheight;y++) {
			icury=floor(cury);
			fracy=cury-(double)icury;
			if (fracy<0 || fracy>1) {
				logwarn("round error fracy=%d",fracy);
			}
			curx=0.5;
			
			if (fracy>=0.5) {
				coefy1=CUBIC_BEZIER_COEF(1.5-fracy);
			} else {
				coefy1=CUBIC_BEZIER_COEF(0.5+fracy);
			}
			coefy2=1.0-coefy1;
			
			for (x=0;x<newwidth;x++) {
				icurx=floor(curx);
				fracx=curx-(double)icurx;
				if (fracx<0 || fracx>1) {
					logwarn("round error fracx=%d",fracx);
				}

				/* fucking sub-pixels with bi-cubic interpolation */
				if (fracx>=0.5) {
					coef1=CUBIC_BEZIER_COEF(1.5-fracx);  /* 1.0 -> 0.5 */
					//coef2=_internal_ImageResizeSplineCoef(-0.5+fracx); /* 0.0 -> 0.5 */
					coef2=1.0-coef1;
					tr=pixels[(icurx+icury*width)*3+3]*coef2;
					tv=pixels[(icurx+icury*width)*3+4]*coef2;
					tb=pixels[(icurx+icury*width)*3+5]*coef2;
				} else {
					coef1=CUBIC_BEZIER_COEF(0.5+fracx); /* 1.0 -> 0.5 */
					//coef2=_internal_ImageResizeSplineCoef(0.5-fracx); /* 0.0 -> 0.5 */
					coef2=1.0-coef1;
					tr=pixels[(icurx+icury*width)*3-3]*coef2;
					tv=pixels[(icurx+icury*width)*3-2]*coef2;
					tb=pixels[(icurx+icury*width)*3-1]*coef2;
				}
				tr+=pixels[(icurx+icury*width)*3+0]*coef1;
				tv+=pixels[(icurx+icury*width)*3+1]*coef1;
				tb+=pixels[(icurx+icury*width)*3+2]*coef1;
				
				if (fracy>=0.5) {
					tr+=pixels[(icurx+icury*width+width)*3+0]*coefy2;
					tv+=pixels[(icurx+icury*width+width)*3+1]*coefy2;
					tb+=pixels[(icurx+icury*width+width)*3+2]*coefy2;
				} else {
					tr+=pixels[(icurx+icury*width-width)*3+0]*coefy2;
					tv+=pixels[(icurx+icury*width-width)*3+1]*coefy2;
					tb+=pixels[(icurx+icury*width-width)*3+2]*coefy2;
				}
				tr+=pixels[(icurx+icury*width)*3+0]*coefy1;
				tv+=pixels[(icurx+icury*width)*3+1]*coefy1;
				tb+=pixels[(icurx+icury*width)*3+2]*coefy1;
				
				newpix[dst++]=(unsigned char)MinMaxInt(tr*0.5+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(tv*0.5+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(tb*0.5+0.5,0,255);
				curx+=vx;
			}
			cury+=vy;
		}
	} else {
		fracy=cury=0.5;
		icury=0;
		for (y=0;y<newheight;y++) {
			cury+=vy;
			iendy=floor(cury);
			fracyend=cury-(double)iendy;
			fracx=curx=0.5;
			icurx=floor(curx);
			coefy1=CUBIC_BEZIER_COEF(1.0-fracy);
			coefy2=CUBIC_BEZIER_COEF(fracyend);
			for (x=0;x<newwidth;x++) {
				curx+=vx;
				iendx=floor(curx);
				fracxend=curx-(double)iendx;
				coefx1=CUBIC_BEZIER_COEF(1.0-fracx);
				coefx2=CUBIC_BEZIER_COEF(fracxend);
				
				pcount=tr=tv=tb=0.0;
				/* fully accurate sub-pixels with bi-cubic clipping */
				for (suby=icury;suby<=iendy;suby++) {
					for (subx=icurx;subx<=iendx;subx++) {
						/* clipping */
						if (suby==icury) {
							coef1=coefy1;
						} else if (suby==iendy) {
							coef1=coefy2;
						} else {
							coef1=1.0;
						}
						if (subx==icurx) {
							coef1*=coefx1;
						} else if (subx==iendx) {
							coef1*=coefx2;
						}

						tr+=pixels[(subx+suby*width)*3+0]*coef1;
						tv+=pixels[(subx+suby*width)*3+1]*coef1;
						tb+=pixels[(subx+suby*width)*3+2]*coef1;
						pcount+=coef1;
					}
				}

				pcount=1.0/pcount;
				newpix[dst++]=(unsigned char)MinMaxInt(tr*pcount+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(tv*pcount+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(tb*pcount+0.5,0,255);

				icurx=iendx;
				fracx=fracxend;
			}
			icury=iendy;
			fracy=fracyend;
		}
	}
	return newpix;
}
unsigned char *ImageResize32(unsigned char *pixels, int width, int height, int newwidth, int newheight)
{
	#undef FUNC
	#define FUNC "ImageResize32"

	unsigned char *newpix;
	double tr,tv,tb,ta;
	double curx,cury,vx,vy,fracx,fracy,pcount,coef1,coef2,fracxend,fracyend,coefy1,coefy2,coefx1,coefx2;
	int x,y,icurx,icury,dst=0,subx,suby,iendx,iendy;

	newpix=MemMalloc(newwidth*newheight*4);
	vx=(double)(width-1)/(double)newwidth;
	vy=(double)(height-1)/(double)newheight;

	if (vx<=1.0 && vy<=1.0) {
		cury=0.5;
		for (y=0;y<newheight;y++) {
			icury=floor(cury);
			fracy=cury-(double)icury;
			if (fracy<0 || fracy>1) {
				logwarn("round error fracy=%d",fracy);
			}
			curx=0.5;
			
			if (fracy>=0.5) {
				coefy1=CUBIC_BEZIER_COEF(1.5-fracy);
			} else {
				coefy1=CUBIC_BEZIER_COEF(0.5+fracy);
			}
			coefy2=1.0-coefy1;
			
			for (x=0;x<newwidth;x++) {
				icurx=floor(curx);
				fracx=curx-(double)icurx;
				if (fracx<0 || fracx>1) {
					logwarn("round error fracx=%d",fracx);
				}

				/* fucking sub-pixels with bi-cubic interpolation */
				if (fracx>=0.5) {
					coef1=CUBIC_BEZIER_COEF(1.5-fracx);  /* 1.0 -> 0.5 */
					//coef2=_internal_ImageResizeSplineCoef(-0.5+fracx); /* 0.0 -> 0.5 */
					coef2=1.0-coef1;
					tr=pixels[(icurx+icury*width)*4+4]*coef2;
					tv=pixels[(icurx+icury*width)*4+5]*coef2;
					tb=pixels[(icurx+icury*width)*4+6]*coef2;
					ta=pixels[(icurx+icury*width)*4+7]*coef2;
				} else {
					coef1=CUBIC_BEZIER_COEF(0.5+fracx); /* 1.0 -> 0.5 */
					//coef2=_internal_ImageResizeSplineCoef(0.5-fracx); /* 0.0 -> 0.5 */
					coef2=1.0-coef1;
					tr=pixels[(icurx+icury*width)*4-4]*coef2;
					tv=pixels[(icurx+icury*width)*4-3]*coef2;
					tb=pixels[(icurx+icury*width)*4-2]*coef2;
					ta=pixels[(icurx+icury*width)*4-1]*coef2;
				}
				tr+=pixels[(icurx+icury*width)*4+0]*coef1;
				tv+=pixels[(icurx+icury*width)*4+1]*coef1;
				tb+=pixels[(icurx+icury*width)*4+2]*coef1;
				ta+=pixels[(icurx+icury*width)*4+3]*coef1;
				
				if (fracy>=0.5) {
					tr+=pixels[(icurx+icury*width+width)*4+0]*coefy2;
					tv+=pixels[(icurx+icury*width+width)*4+1]*coefy2;
					tb+=pixels[(icurx+icury*width+width)*4+2]*coefy2;
					ta+=pixels[(icurx+icury*width+width)*4+3]*coefy2;
				} else {
					tr+=pixels[(icurx+icury*width-width)*4+0]*coefy2;
					tv+=pixels[(icurx+icury*width-width)*4+1]*coefy2;
					tb+=pixels[(icurx+icury*width-width)*4+2]*coefy2;
					ta+=pixels[(icurx+icury*width-width)*4+3]*coefy2;
				}
				tr+=pixels[(icurx+icury*width)*4+0]*coefy1;
				tv+=pixels[(icurx+icury*width)*4+1]*coefy1;
				tb+=pixels[(icurx+icury*width)*4+2]*coefy1;
				ta+=pixels[(icurx+icury*width)*4+3]*coefy1;
				
				newpix[dst++]=(unsigned char)MinMaxInt(tr*0.5+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(tv*0.5+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(tb*0.5+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(ta*0.5+0.5,0,255);
				curx+=vx;
			}
			cury+=vy;
		}
	} else {
		fracy=cury=0.5;
		icury=0;
		for (y=0;y<newheight;y++) {
			cury+=vy;
			iendy=floor(cury);
			fracyend=cury-(double)iendy;
			fracx=curx=0.5;
			icurx=floor(curx);
			coefy1=CUBIC_BEZIER_COEF(1.0-fracy);
			coefy2=CUBIC_BEZIER_COEF(fracyend);
			for (x=0;x<newwidth;x++) {
				curx+=vx;
				iendx=floor(curx);
				fracxend=curx-(double)iendx;
				coefx1=CUBIC_BEZIER_COEF(1.0-fracx);
				coefx2=CUBIC_BEZIER_COEF(fracxend);
				
				pcount=tr=tv=tb=ta=0.0;
				/* fully accurate sub-pixels with bi-cubic clipping */
				for (suby=icury;suby<=iendy;suby++) {
					for (subx=icurx;subx<=iendx;subx++) {
						/* clipping */
						if (suby==icury) {
							coef1=coefy1;
						} else if (suby==iendy) {
							coef1=coefy2;
						} else {
							coef1=1.0;
						}
						if (subx==icurx) {
							coef1*=coefx1;
						} else if (subx==iendx) {
							coef1*=coefx2;
						}

						tr+=pixels[(subx+suby*width)*4+0]*coef1;
						tv+=pixels[(subx+suby*width)*4+1]*coef1;
						tb+=pixels[(subx+suby*width)*4+2]*coef1;
						ta+=pixels[(subx+suby*width)*4+3]*coef1;
						pcount+=coef1;
					}
				}

				pcount=1.0/pcount;
				newpix[dst++]=(unsigned char)MinMaxInt(tr*pcount+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(tv*pcount+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(tb*pcount+0.5,0,255);
				newpix[dst++]=(unsigned char)MinMaxInt(ta*pcount+0.5,0,255);

				icurx=iendx;
				fracx=fracxend;
			}
			icury=iendy;
			fracy=fracyend;
		}
	}
	return newpix;
}

#define ImageReduction ImageResize
#define ImageReduction32 ImageResize32

unsigned char *ImageCanvasSize(unsigned char *pixels, int width, int height, int addup, int adddown, int addleft, int addright, unsigned int FILL)
{
	#undef FUNC
	#define FUNC "ImageCanvasSize"

	unsigned char *newpixels;
	int startx,starty,endx,endy;
	int sizex,sizey;
	int putx,puty;
	int x,y;
	int srcy,cury;
	
	sizex=width+addleft+addright;
	sizey=height+addup+adddown;
	if (sizex<1 || sizey<1) {
		logwarn("cannot resize image because canvas size is negative or null");
		return NULL;
	}
	newpixels=MemMalloc(sizex*sizey*sizeof(unsigned int));
	if (!FILL) {
		/*@@@ to optimize */
		MemSet(newpixels,0,sizex*sizey*3);
	} else {
		for (y=0;y<sizey;y++) {
			for (x=0;x<sizex;x++) {
				newpixels[y*sizey*3+x*3+0]=(FILL&0xFF0000)>>16;
				newpixels[y*sizey*3+x*3+1]=(FILL&0xFF00)>>8;
				newpixels[y*sizey*3+x*3+2]=FILL&0xFF;
			}
		}
	}
	
	/* compute region */
	if (addleft>=0) {
		startx=0;
		putx=addleft;
	} else {
		startx=-addleft;
		putx=0;
	}
	if (addup>=0) {
		starty=0;
		puty=addup;
	} else {
		starty=-addup;
		puty=0;
	}
	if (addright>=0) {
		endx=width;
	} else {
		endx=width+addright;
	}
	if (adddown>=0) {
		endy=height;
	} else {
		endy=height+adddown;
	}

	/* copy bitmap */
	srcy=starty*width*3;
	cury=puty*sizex*3;
	for (y=starty;y<endy;y++) {
		for (x=startx;x<endx;x++) {
			newpixels[cury+x*3+0]=pixels[srcy+x*3+0];
			newpixels[cury+x*3+1]=pixels[srcy+x*3+1];
			newpixels[cury+x*3+2]=pixels[srcy+x*3+2];
		}
		srcy+=width*3;
		cury+=sizex*3;
	}
	
	return newpixels;
}

unsigned int *ImageCanvasSize32(unsigned int *pixels, int width, int height, int addup, int adddown, int addleft, int addright, unsigned int FILL)
{
	#undef FUNC
	#define FUNC "ImageCanvasSize32"

	unsigned int *newpixels;
	int startx,starty,endx,endy;
	int sizex,sizey;
	int putx,puty;
	int x,y;
	int srcy,cury;
	
	sizex=width+addleft+addright;
	sizey=height+addup+adddown;
	if (sizex<1 || sizey<1) {
		logwarn("cannot resize image because canvas size is negative or null");
		return NULL;
	}
	newpixels=MemMalloc(sizex*sizey*sizeof(unsigned int));
	if (!FILL) {
		/*@@@ to optimize */
		MemSet(newpixels,0,sizex*sizey*3);
	} else {
		for (x=0;x<sizex*sizey;x++) {
			newpixels[x]=FILL;
		}
	}
	
	/* compute region */
	if (addleft>=0) {
		startx=0;
		putx=addleft;
	} else {
		startx=-addleft;
		putx=0;
	}
	if (addup>=0) {
		starty=0;
		puty=addup;
	} else {
		starty=-addup;
		puty=0;
	}
	if (addright>=0) {
		endx=width;
	} else {
		endx=width+addright;
	}
	if (adddown>=0) {
		endy=height;
	} else {
		endy=height+adddown;
	}

	/* copy bitmap */
	srcy=starty*width;
	cury=puty*sizex;
	for (y=starty;y<endy;y++) {
		for (x=startx;x<endx;x++) {
			newpixels[cury+x]=pixels[srcy+x];
		}
		srcy+=width;
		cury+=sizex;
	}
	
	return newpixels;
}

unsigned char * ImageCrop(unsigned char *pixels, int width, int height, int xstart, int ystart, int sizex, int sizey)
{
	#undef FUNC
	#define FUNC "ImageCrop"
	
	return ImageCanvasSize(pixels,width,height,-ystart,sizey-height+ystart,-xstart,sizex-width+xstart,0);
}
unsigned int * ImageCrop32(unsigned int *pixels, int width, int height, int xstart, int ystart, int sizex, int sizey)
{
	#undef FUNC
	#define FUNC "ImageCrop32"
	
	return ImageCanvasSize32(pixels,width,height,-ystart,sizey-height+ystart,-xstart,sizex-width+xstart,0);
}
#define PNG_HEADER_SIZE 8

struct s_png_info {
	int width;
	int height;
	int bit_depth;
	int color_type;
	int filter_method;
	int compression_type;
	int interlace_type;

	unsigned char *data;
};

void PNGFree(struct s_png_info **png)
{
	#undef FUNC
	#define FUNC "FreePNG"

	if (!png[0]) return;
	if (png[0]->data) MemFree(png[0]->data);
	MemFree(png[0]);
	*png=NULL;
}

/***
	PNGInit

	Allocate a new PNG structure
	If a reference PNG structure is given, then copy info to the new struct
*/
struct s_png_info * PNGInit(struct s_png_info *photo)
{
	#undef FUNC
	#define FUNC "PNGInit"

	struct s_png_info *new_photo;

	new_photo=MemCalloc(sizeof(struct s_png_info));
	if (photo) {
		*new_photo=*photo;
		new_photo->data=NULL;
	}
	return new_photo;
}
struct s_png_info * PNGInitTrueColor()
{
	#undef FUNC
	#define FUNC "PNGInitTrueColor"

	struct s_png_info pngproto={0};
	pngproto.bit_depth=8;
	pngproto.color_type=2;
	pngproto.compression_type=0;
	return PNGInit(&pngproto);
}
struct s_png_info * _internal_PNGRead(char *filename, int want8, int wantALPHA)
{
	#undef FUNC
	#define FUNC "PNGRead"

	FILE *fp;
	int i,pixel_size,j;
	unsigned char **libpng_data;
	png_structp png_ptr;
	png_infop   info_ptr;
	char png_header[PNG_HEADER_SIZE];
	struct s_png_info *png_info;
	/* alpha test */
	png_bytep trans_alpha = NULL;
	int num_trans = 0;
	png_color_16p trans_color = NULL;
	int expand16=0;
	int packedpixel;


	/* we must read 8 byte of the supposed png file for libpng, cause they can't open png file (crappy coders make crappy code) */
	FileReadBinary(filename,png_header,PNG_HEADER_SIZE);
	FileReadBinaryClose(filename);

	/* legacy libpng code */
	if (png_sig_cmp(png_header,0,PNG_HEADER_SIZE)) {
		logerr("This file is not a PNG picture");
		exit(INTERNAL_ERROR);
	}
	if ((png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL))==NULL) {
		png_destroy_read_struct(&png_ptr,(png_infopp)NULL,(png_infopp)NULL);
		logerr("PngLib error: cannot create read struct");
		exit(INTERNAL_ERROR);
	}
	if ((info_ptr=png_create_info_struct(png_ptr))==NULL) {
		png_destroy_read_struct(&png_ptr,&info_ptr,(png_infopp)NULL);
		logerr("PngLib error: cannot create info struct");
		exit(INTERNAL_ERROR);
	}
	
	/* libpng cannot open png file by itself, so we do (crappy coders...) */
	fp=fopen(filename,"rb");
	png_init_io(png_ptr,fp);

	png_read_info(png_ptr,info_ptr);

	png_info=MemMalloc(sizeof(struct s_png_info));
	png_info->width=png_get_image_width(png_ptr,info_ptr);
	png_info->height=png_get_image_height(png_ptr,info_ptr);
	png_info->bit_depth=png_get_bit_depth(png_ptr,info_ptr);
	png_info->color_type=png_get_color_type(png_ptr,info_ptr);
	switch (png_info->color_type) {
		case PNG_COLOR_TYPE_PALETTE:
			png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, &trans_color);
			if (trans_alpha != NULL) {
				png_info->color_type=PNG_COLOR_TYPE_RGBA;
				//loginfo("PNG palette -> RGBA");
				pixel_size=4;
			} else {
				png_info->color_type=PNG_COLOR_TYPE_RGB;
				//loginfo("PNG palette -> RGB");
				pixel_size=3;
			}
			png_set_palette_to_rgb(png_ptr);
			break;
		case PNG_COLOR_TYPE_GRAY:
				pixel_size=3;
				png_set_gray_to_rgb(png_ptr);
				break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:png_set_gray_to_rgb(png_ptr);
				pixel_size=4;
				break;
		case PNG_COLOR_TYPE_RGB:
				pixel_size=3;
				break;
		case PNG_COLOR_TYPE_RGBA:
				pixel_size=4;
				break;
		default:
			logerr("unsupported PNG format -> color_type=%d",png_info->color_type);
			break;
	}
	//loginfo("Loading PNG [%dx%d] bt=%d  %s",png_info->width,png_info->height,png_info->bit_depth,filename);

	//png_set_invert_alpha(png_ptr); /* alpha is transparency 0:opaque 255/65535:fully transparent */

	switch (wantALPHA) {
		case 0:
			/* desactive le canal ALPHA si on n'en veut pas */
			if (png_info->color_type & PNG_COLOR_MASK_ALPHA) {
				png_set_strip_alpha(png_ptr);
				//loginfo("PNG RGBA -> RGB");
				pixel_size=3;
			}
			break;
		default:
			/* si la transparence n'est pas ALPHA on en fait un masque ALPHA */
			if (png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS)) {
				png_set_tRNS_to_alpha(png_ptr);
				//loginfo("PNG make Alpha channel");
				pixel_size=4;
			}
	}

	if (png_info->bit_depth==16) {
		if (want8) {
			//loginfo("PNG 16 bits -> 8 bits");
			png_set_strip_16(png_ptr);
			png_info->bit_depth=8;
		}
		else {
			png_set_swap(png_ptr); /* little-endian requested */
			pixel_size*=2;
		}
	} else if (png_info->bit_depth==8) {
		if (!want8) {
			pixel_size*=2;
			expand16=1;
		}
	} else if (png_info->bit_depth<8) {
		loginfo("");
		png_set_packing(png_ptr);
	}

	/* libpng does not handle linear memory... */
	libpng_data=MemMalloc(sizeof(char*)*png_info->height);
	for (i=0;i<png_info->height;i++) {
		libpng_data[i]=MemMalloc(pixel_size*png_info->width);
	}
	png_read_image(png_ptr,(png_bytepp)libpng_data);

	switch (png_info->color_type) {
		case PNG_COLOR_TYPE_PALETTE:loginfo("RGB ou RGBA du coup?");break;
		default:break;
	}

	/* copy each rows to linear memory */
	png_info->data=MemMalloc(pixel_size*png_info->width*png_info->height);
	for (i=0;i<png_info->height;i++) {
		MemCpy(png_info->data+i*pixel_size*png_info->width,libpng_data[i],pixel_size*png_info->width);
	}
	/* free crappy png row memory */
	for (i=0;i<png_info->height;i++) {
		MemFree(libpng_data[i]);
	}
	MemFree(libpng_data);

	/* cause libpng cannot close file by itself... */
	fclose(fp);
	png_destroy_read_struct(&png_ptr,&info_ptr,(png_infopp)NULL);

	switch (wantALPHA) {
		case 0:png_info->color_type=PNG_COLOR_TYPE_RGB;break;
		case 1:
			if (png_info->color_type!=PNG_COLOR_TYPE_RGBA) {
				if (png_info->bit_depth==8 && png_info->color_type==PNG_COLOR_TYPE_RGB) {
					loginfo("Make empty Alpha channel");
					png_info->color_type=PNG_COLOR_TYPE_RGBA;
					png_info->data=ImageFreeRGBToRGBA(png_info->data,png_info->width,png_info->height);
				} else if (png_info->bit_depth==16 && png_info->color_type==PNG_COLOR_TYPE_RGB) {
					loginfo("Make empty 16bits Alpha channel");
					png_info->color_type=PNG_COLOR_TYPE_RGBA;
					png_info->data=ImageFreeRRGGBBToRRGGBBAA(png_info->data,png_info->width,png_info->height);
				} else {
					logerr("INTERNAL ERROR - cannot process PNG BD:%d CT:%d",png_info->bit_depth,png_info->color_type);
					exit(INTERNAL_ERROR);
				}
			}
		default:break;
	}
	if (expand16) {
		png_info->bit_depth=16;
		if (PNG_COLOR_TYPE_RGB) {
			packedpixel=6;
		} else {
			packedpixel=8;
		}
		j=png_info->height*png_info->width*packedpixel-packedpixel;
		i=png_info->height*png_info->width*packedpixel/2-packedpixel/2;
		loginfo("Expand 8bits PNG %sto 16bits",packedpixel==8?"(+Apha) ":"");
		while (i>=0) {
			png_info->data[j+0]=0;
			png_info->data[j+1]=png_info->data[i+0];
			png_info->data[j+2]=0;
			png_info->data[j+3]=png_info->data[i+1];
			png_info->data[j+4]=0;
			png_info->data[j+5]=png_info->data[i+2];
			if (packedpixel==8) {
				png_info->data[j+6]=0;
				png_info->data[j+7]=png_info->data[i+3];
				i-=4;
				j-=8;
			} else {
				i-=3;
				j-=6;
			}
		}
	}

	return png_info;
}

#define PNGRead(filename) _internal_PNGRead(filename,-1,-1)
#define PNGRead64(filename) _internal_PNGRead(filename,0,1)
#define PNGRead48(filename) _internal_PNGRead(filename,0,0)
#define PNGRead32(filename) _internal_PNGRead(filename,1,1)
#define PNGRead24(filename) _internal_PNGRead(filename,1,0)

void PNGWriteCallBack(png_structp png_ptr, png_uint_32 row, int pass)
{
	#undef FUNC
	#define FUNC "PNGWriteCallBack"
	printf("row: %d (%d)\r",(int)row,pass);
}

void PNGWrite(struct s_png_info *photo, char *filename)
{
	#undef FUNC
	#define FUNC "PNGWrite"

	int i;
	FILE *fp;
	unsigned char **libpng_data;
	png_structp png_ptr;
	png_infop   info_ptr;
	png_text    text_ptr={0};
printf("grouik\n");
	if ((png_ptr=png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL))==NULL) {
		logerr("PngLib error: cannot create write struct");
		exit(INTERNAL_ERROR);
	}
	if ((info_ptr=png_create_info_struct(png_ptr))==NULL) {
		png_destroy_write_struct(&png_ptr,NULL);
		logerr("PngLib error: cannot create info struct");
		exit(INTERNAL_ERROR);
	}
	fp=fopen(filename,"wb");
	if (!fp) {
		logerr("Cannot create [%s] for writing",filename);
		exit(INTERNAL_ERROR);
	}
	png_init_io(png_ptr,fp);
	png_set_write_status_fn(png_ptr,PNGWriteCallBack);
	png_set_compression_level(png_ptr,Z_DEFAULT_COMPRESSION); /* best compromise between speed and compression ratio */
	png_set_IHDR(png_ptr,info_ptr,photo->width,photo->height,photo->bit_depth,photo->color_type,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_DEFAULT,PNG_FILTER_TYPE_DEFAULT);
	
	/*
	text_ptr.compression=PNG_TEXT_COMPRESSION_NONE;
	strcpy(text_ptr.key,"Copyright");
	text_ptr.text=TxtStrDup("image created with %s using LibPNG dot org",LIBRARY_LABEL);
	strcpy(text_ptr.lang,"EN");
	png_set_text(png_ptr,info_ptr,text_ptr,1);
	MemFree(text_ptr.text);
	*/

	/* libpng does not handle linear memory... */
	libpng_data=MemMalloc(sizeof(char*)*photo->height);
	for (i=0;i<photo->height;i++) {
		libpng_data[i]=MemMalloc(3*photo->width);
	}
	/* copy each rows from linear memory */
	switch (photo->color_type) {
		default:
		case PNG_COLOR_TYPE_RGB:
			for (i=0;i<photo->height;i++) {
				memcpy(libpng_data[i],photo->data+i*3*photo->width,3*photo->width);
			}
			break;
		case PNG_COLOR_TYPE_RGBA:
			for (i=0;i<photo->height;i++) {
				for (int j=0;j<photo->width;j++) {
					libpng_data[i][j*3+0]=photo->data[i*4*photo->width+0+j*4];
					libpng_data[i][j*3+1]=photo->data[i*4*photo->width+1+j*4];
					libpng_data[i][j*3+2]=photo->data[i*4*photo->width+2+j*4];
				}
			}
			break;
	}

	/* then assign them to png struct */
	png_set_rows(png_ptr,info_ptr,libpng_data);
	png_write_png(png_ptr,info_ptr,PNG_TRANSFORM_IDENTITY,NULL);

	/* free crappy png row memory */
	for (i=0;i<photo->height;i++) {
		MemFree(libpng_data[i]);
	}
	MemFree(libpng_data);

        /* cause libpng cannot close file by itself... */
        fclose(fp);
        png_destroy_write_struct(&png_ptr,&info_ptr);

	loginfo("Writing PNG [%dx%d] %s %s",photo->width,photo->height,filename,photo->color_type==PNG_COLOR_TYPE_RGBA?"from RGBA":"from RGB");
}


#define FASTFLOOR(x) ( ((x)>0) ? ((int)x) : (((int)x)-1) )

unsigned char g_simplex_perm[512] = {151,160,137,91,90,15,
  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
  151,160,137,91,90,15,
  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 
};

float  _internal_SimplexNoiseGrad( int hash, float x ) {
	#undef FUNC
	#define FUNC "_internal_SimplexNoiseGrad"

    int h = hash & 15;
    float grad = 1.0f + (h & 7);   // Gradient value 1.0, 2.0, ..., 8.0
    if (h&8) grad = -grad;         // Set a random sign for the gradient
    return ( grad * x );           // Multiply the gradient with the distance
}

float  _internal_SimplexNoiseGrad2D( int hash, float x, float y ) {
	#undef FUNC
	#define FUNC "_internal_SimplexNoiseGrad2D"

int h;
float u,v;
    h = hash & 7;      // Convert low 3 bits of hash code
    u = h<4 ? x : y;  // into 8 simple gradient directions,
    v = h<4 ? y : x;  // and compute the dot product with (x,y).
    return ((h&1)? -u : u) + ((h&2)? -2.0f*v : 2.0f*v);
}


  // A lookup table to traverse the simplex around a given point in 4D.
  // Details can be found where this table is used, in the 4D noise method.
  /* TODO: This should not be required, backport it from Bill's GLSL code! */
  static unsigned char simplex[64][4] = {
    {0,1,2,3},{0,1,3,2},{0,0,0,0},{0,2,3,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,2,3,0},
    {0,2,1,3},{0,0,0,0},{0,3,1,2},{0,3,2,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,3,2,0},
    {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
    {1,2,0,3},{0,0,0,0},{1,3,0,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,3,0,1},{2,3,1,0},
    {1,0,2,3},{1,0,3,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,0,3,1},{0,0,0,0},{2,1,3,0},
    {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
    {2,0,1,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,0,1,2},{3,0,2,1},{0,0,0,0},{3,1,2,0},
    {2,1,0,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,1,0,2},{0,0,0,0},{3,2,0,1},{3,2,1,0}};

// 1D simplex noise
float SimplexNoise(float x) {
	#undef FUNC
	#define FUNC "SimplexNoise"

int i0,i1;
float x0,x1,n0,n1,t0,t1;

  i0 = FASTFLOOR(x);
  i1 = i0 + 1;
  x0 = x - i0;
  x1 = x0 - 1.0f;


 t0 = 1.0f - x0*x0;
//  if(t0 < 0.0f) t0 = 0.0f;
  t0 *= t0;
  n0 = t0 * t0 * _internal_SimplexNoiseGrad(g_simplex_perm[i0 & 0xff], x0);

  t1 = 1.0f - x1*x1;
//  if(t1 < 0.0f) t1 = 0.0f;
  t1 *= t1;
  n1 = t1 * t1 * _internal_SimplexNoiseGrad(g_simplex_perm[i1 & 0xff], x1);
  // The maximum value of this noise is 8*(3/4)^4 = 2.53125
  // A factor of 0.395 would scale to fit exactly within [-1,1], but
  // we want to match PRMan's 1D noise, so we scale it down some more.
  return 0.25f * (n0 + n1);

}

// 2D simplex noise
float SimplexNoise2D(float x, float y) {
	#undef FUNC
	#define FUNC "SimplexNoise2D"


#define F2 0.366025403 // F2 = 0.5*(sqrt(3.0)-1.0)
#define G2 0.211324865 // G2 = (3.0-Math.sqrt(3.0))/6.0

    float n0, n1, n2; // Noise contributions from the three corners
float s,xs,ys,t,X0,Y0,x0,y0,x1,x2,y1,y2,t0,t1,t2;
int ii,jj,i1,j1,i,j;

    // Skew the input space to determine which simplex cell we're in
    s = (x+y)*F2; // Hairy factor for 2D
    xs = x + s;
    ys = y + s;
    i = FASTFLOOR(xs);
    j = FASTFLOOR(ys);

    t = (float)(i+j)*G2;
    X0 = i-t; // Unskew the cell origin back to (x,y) space
    Y0 = j-t;
    x0 = x-X0; // The x,y distances from the cell origin
    y0 = y-Y0;

    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    else {i1=0; j1=1;}      // upper triangle, YX order: (0,0)->(0,1)->(1,1)

    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6

    x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    y1 = y0 - j1 + G2;
    x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
    y2 = y0 - 1.0f + 2.0f * G2;

    // Wrap the integer indices at 256, to avoid indexing perm[] out of bounds
    ii = i & 0xff;
    jj = j & 0xff;

    // Calculate the contribution from the three corners
    t0 = 0.5f - x0*x0-y0*y0;
    if(t0 < 0.0f) n0 = 0.0f;
    else {
      t0 *= t0;
      n0 = t0 * t0 * _internal_SimplexNoiseGrad2D(g_simplex_perm[ii+g_simplex_perm[jj]], x0, y0); 
    }

    t1 = 0.5f - x1*x1-y1*y1;
    if(t1 < 0.0f) n1 = 0.0f;
    else {
      t1 *= t1;
      n1 = t1 * t1 * _internal_SimplexNoiseGrad2D(g_simplex_perm[ii+i1+g_simplex_perm[jj+j1]], x1, y1);
    }

    t2 = 0.5f - x2*x2-y2*y2;
    if(t2 < 0.0f) n2 = 0.0f;
    else {
      t2 *= t2;
      n2 = t2 * t2 * _internal_SimplexNoiseGrad2D(g_simplex_perm[ii+1+g_simplex_perm[jj+1]], x2, y2);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 40.0f * (n0 + n1 + n2); // TODO: The scale factor is preliminary!
}

int ImageFillSurface(unsigned char *data, int sizex, int sizey,int x, int y, unsigned int color)
{
	#undef FUNC
	#define FUNC "ImageFillSurface"

	int minx,maxx,i;
	int refR,refV,refB;
	int putR,putV,putB;
	
	if (x<0 || x>=sizex) return 0;
	if (y<0 || y>=sizey) return 0;

	refR=data[x*3+y*sizex*3];
	refV=data[x*3+y*sizex*3+1];
	refB=data[x*3+y*sizex*3+2];
	putR=(color&0xFF0000)>>16;
	putV=(color&0xFF00)>>8;
	putB=color&0xFF;
	if (putR==refR && putV==refV && putB==refB) return x;
	data[x*3+y*sizex*3]=putR;
	data[x*3+y*sizex*3+1]=putV;
	data[x*3+y*sizex*3+2]=putB;
	
	minx=x-1;	
	while (data[minx*3+y*sizex*3]==refR && data[minx*3+y*sizex*3+1]==refV && data[minx*3+y*sizex*3+2]==refB && minx>=0) {
		data[minx*3+y*sizex*3]=putR;
		data[minx*3+y*sizex*3+1]=putV;
		data[minx*3+y*sizex*3+2]=putB;
		minx--;
	}
	maxx=x+1;	
	while (data[maxx*3+y*sizex*3]==refR && data[maxx*3+y*sizex*3+1]==refV && data[maxx*3+y*sizex*3+2]==refB && maxx<sizex) {
		data[maxx*3+y*sizex*3]=putR;
		data[maxx*3+y*sizex*3+1]=putV;
		data[maxx*3+y*sizex*3+2]=putB;
		maxx++;
	}
	
	if (maxx>=sizex) maxx=sizex;
	
	if (y<sizey-1) {
		for (i=minx+1;i<maxx;i++) {
			if (data[i*3+(y+1)*sizex*3]==refR && data[i*3+(y+1)*sizex*3+1]==refV && data[i*3+(y+1)*sizex*3+2]==refB) i=ImageFillSurface(data,sizex,sizey,i,y+1,color);
		}
	}
	if (y>0) {
		for (i=minx+1;i<maxx;i++) {
			if (data[i*3+(y-1)*sizex*3]==refR && data[i*3+(y-1)*sizex*3+1]==refV && data[i*3+(y-1)*sizex*3+2]==refB) i=ImageFillSurface(data,sizex,sizey,i,y-1,color);
		}
	}
	return maxx;
}

/***
* Fill a 32 bits image of sizex x sizey starting at x/y using color
* return the highest x coordinate +1 filled
*/
int ImageFillSurface32(unsigned int *data, int sizex, int sizey,int x, int y, unsigned int color)
{
	#undef FUNC
	#define FUNC "ImageFillSurface32"

	int minx,maxx,i;
	unsigned int refcolor;
	
	if (x<0 || x>=sizex) return 0;
	if (y<0 || y>=sizey) return 0;

	refcolor=data[x+y*sizex];
	if (refcolor==color) {
		return x;
	}
	data[x+y*sizex]=color;
	
	minx=x-1;	
	while (data[minx+y*sizex]==refcolor && minx>=0) {
		data[minx+y*sizex]=color;
		minx--;
	}
	maxx=x+1;	
	while (data[maxx+y*sizex]==refcolor && maxx<sizex) {
		data[maxx+y*sizex]=color;
		maxx++;
	}
	
	if (maxx>=sizex) maxx=sizex;

	if (y<sizey-1) {
		for (i=minx+1;i<maxx;i++) {
			if (data[i+(y+1)*sizex]==refcolor) {
				i=ImageFillSurface32(data,sizex,sizey,i,y+1,color);
			}
		}
	}
	if (y>0) {
		for (i=minx+1;i<maxx;i++) {
			if (data[i+(y-1)*sizex]==refcolor) {
				i=ImageFillSurface32(data,sizex,sizey,i,y-1,color);
			}
		}
	}
	return maxx;
}



struct s_raw_info {
	int width;
	int height;
	int nbcolor;
	unsigned char *palette;
	unsigned char *data;
};

void ImageRAWFreeStruct(struct s_raw_info *rawinfo)
{
	#undef FUNC
	#define FUNC "ImageRAWFreeStruct"

	if (rawinfo->palette && rawinfo->nbcolor) MemFree(rawinfo->palette);
	if (rawinfo->data) MemFree(rawinfo->data);
}
void ImageRAWFreeStructPtr(struct s_raw_info **rawinfo)
{
	#undef FUNC
	#define FUNC "ImageRAWFreeStructPtr"

	if (!*rawinfo) return;
	ImageRAWFreeStruct(*rawinfo);
	MemFree(*rawinfo);
	*rawinfo=NULL;
}

void ImageRAWHeaderInfo(unsigned char *header, int *width, int *height, int *nbcolor)
{
	#undef FUNC
	#define FUNC "ImageRAWHeaderInfo"

	if (strncmp(header,"mhwanh",6)==0 && header[7]==4) {
		*width=header[9]+header[8]*256;
		*height=header[11]+header[10]*256;
		*nbcolor=header[13]+header[12]*256;
	} else {
		*width=0;
		*height=0;
		*nbcolor=0;
	}
}
void ImageRAWInfo(char *filename, int *width, int *height, int *nbcolor)
{
	#undef FUNC
	#define FUNC "ImageRAWInfo"

	unsigned char header[32];
	
	FileReadBinary(filename,header,32);
	ImageRAWHeaderInfo(header,width,height,nbcolor);
}
struct s_raw_info *ImageRAWRead(char *filename)
{
	#undef FUNC
	#define FUNC "ImageRAWRead"

	struct s_raw_info *rawinfo=NULL;
	int i,idx,c;

	rawinfo=MemCalloc(sizeof(struct s_raw_info));
	ImageRAWInfo(filename,&rawinfo->width,&rawinfo->height,&rawinfo->nbcolor);
	if (!&rawinfo->width || !&rawinfo->height) return rawinfo;
	/* memory for 24bits pixels */
	rawinfo->data=MemMalloc(rawinfo->width*rawinfo->height*3);
	/* palette or true color? */
	if (rawinfo->nbcolor) {
//loginfo("RAW image with %d colors palette",rawinfo->nbcolor);
		rawinfo->palette=MemMalloc(3*rawinfo->nbcolor);
		FileReadBinary(filename,rawinfo->palette,rawinfo->nbcolor*3);
		FileReadBinary(filename,rawinfo->data+rawinfo->width*rawinfo->height*2,rawinfo->width*rawinfo->height);
		idx=0;
		for (i=rawinfo->width*rawinfo->height*2;i<rawinfo->width*rawinfo->height*3;i++) {
			c=rawinfo->data[i];
			if (c>=rawinfo->nbcolor) {
				logerr("corrupted RAW image date file [%s], palette idx too big (%d>%d)",filename,c,rawinfo->nbcolor);
				exit(ABORT_ERROR);
			}
			rawinfo->data[idx++]=rawinfo->palette[c*3+0];
			rawinfo->data[idx++]=rawinfo->palette[c*3+1];
			rawinfo->data[idx++]=rawinfo->palette[c*3+2];
		}
	} else {
//loginfo("RAW true color image");
		FileReadBinary(filename,rawinfo->data,rawinfo->width*rawinfo->height*3);
	}
	FileReadBinaryClose(filename);
	return rawinfo;
}

int ImageRAWWrite(char *filename, struct s_raw_info *rawinfo)
{
	#undef FUNC
	#define FUNC "ImageRAWWrite"

	unsigned char header[32]={0};
	unsigned char *dataidx=NULL;
	float distance,mindistance;
	int i,c,dmin,flagreduce=0;

	FileRemoveIfExists(filename);

	strcpy(header,"mhwanh");
	header[7]=4; // v4 ?
	header[8]=rawinfo->width>>8;
	header[9]=rawinfo->width&0xFF;
	header[10]=rawinfo->height>>8;
	header[11]=rawinfo->height&0xFF;
	header[12]=rawinfo->nbcolor>>8;
	header[13]=rawinfo->nbcolor&0xFF;
	FileWriteBinary(filename,header,32);
	/* palette or true color? */
	if (rawinfo->nbcolor) {
	//	loginfo("writing palette RAW image");
		dataidx=MemMalloc(rawinfo->width*rawinfo->height);
		for (i=0;i<rawinfo->width*rawinfo->height;i++) {
			for (c=0;c<rawinfo->nbcolor;c++) {
				if (rawinfo->data[i*3+0]==rawinfo->palette[c*3+0]
					&& rawinfo->data[i*3+1]==rawinfo->palette[c*3+1]
					&& rawinfo->data[i*3+2]==rawinfo->palette[c*3+2]) {
					break;
				}
			}
			if (c<rawinfo->nbcolor) {
				dataidx[i]=c;
			} else {
				flagreduce=1;
				dmin=0;
				mindistance=256*256*256;
				for (c=0;c<rawinfo->nbcolor;c++) {
					distance=abs(rawinfo->data[i*3+0]-rawinfo->palette[c*3+0])+abs(rawinfo->data[i*3+1]-rawinfo->palette[c*3+1])+abs(rawinfo->data[i*3+2]-rawinfo->palette[c*3+2]);
					if (distance<mindistance) {
						dmin=c;
						mindistance=distance;
					}
				}
				dataidx[i]=dmin;
			}
		}
	//	if (flagreduce) logwarn("colors approximation when saving RAW image");
		FileWriteBinary(filename,rawinfo->palette,rawinfo->nbcolor*3);
		FileWriteBinary(filename,dataidx,rawinfo->width*rawinfo->height);
		MemFree(dataidx);
	} else {
	//	loginfo("writing true color RAW image");
		FileWriteBinary(filename,rawinfo->data,rawinfo->width*rawinfo->height*3);
	}
	FileWriteBinaryClose(filename);
}






#undef __FILENAME__

/************************************
	end of mini-library
********************************EOF*/
