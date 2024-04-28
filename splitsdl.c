#ifndef OS_WIN
#define DEBUG_MODE 0
#else
#define FAST_LIBRARY 1
#endif

#include "library.c"
#include "libgfx.c"
#include<float.h>

#ifndef OS_WIN
#include <SDL2/SDL.h>
#else
#include <SDL.h>	
#endif

#define __FILENAME__ "splitsdl.c"

#define WINDOW_NAME "splitraster+ 40 years Edition"



struct s_hardware_sprite {
unsigned char data[256*3];
unsigned char mask[256];
unsigned char palette[45+3];
int x,y,group,active,moving;
};

struct s_undo {
	struct s_hardware_sprite hsp[16];
	float floydcoef;
	float sharpnesscoef;
	float contrastcoef;
	int leveldown;
	int levelup;
};


void HSP_fill(struct s_hardware_sprite *hsp, int sx, int sy) {
	unsigned int c;

	c=hsp->data[(sx+sy*16)*3+0]+(hsp->data[(sx+sy*16)*3+1]<<8)+(hsp->data[(sx+sy*16)*3+2]<<16);
	hsp->mask[sx+sy*16]=0;

	if (sx<15 && hsp->mask[sx+1+sy*16] && (hsp->data[(sx+1+sy*16)*3+0]+(hsp->data[(sx+1+sy*16)*3+1]<<8)+(hsp->data[(sx+1+sy*16)*3+2]<<16))==c) HSP_fill(hsp,sx+1,sy);
	if (sx>0 &&  hsp->mask[sx-1+sy*16] && (hsp->data[(sx-1+sy*16)*3+0]+(hsp->data[(sx-1+sy*16)*3+1]<<8)+(hsp->data[(sx-1+sy*16)*3+2]<<16))==c) HSP_fill(hsp,sx-1,sy);
	if (sy<15 && hsp->mask[sx+sy*16+16] && (hsp->data[(sx+sy*16+16)*3+0]+(hsp->data[(sx+sy*16+16)*3+1]<<8)+(hsp->data[(sx+sy*16+16)*3+2]<<16))==c) HSP_fill(hsp,sx,sy+1);
	if (sy>0 &&  hsp->mask[sx+sy*16-16] && (hsp->data[(sx+sy*16-16)*3+0]+(hsp->data[(sx+sy*16-16)*3+1]<<8)+(hsp->data[(sx+sy*16-16)*3+2]<<16))==c) HSP_fill(hsp,sx,sy-1);
}
void HSP_unfill(struct s_hardware_sprite *hsp, int sx, int sy) {
	unsigned int c;

	c=hsp->data[(sx+sy*16)*3+0]+(hsp->data[(sx+sy*16)*3+1]<<8)+(hsp->data[(sx+sy*16)*3+2]<<16);
	hsp->mask[sx+sy*16]=1;

	if (sx<15 && !hsp->mask[sx+1+sy*16] && (hsp->data[(sx+1+sy*16)*3+0]+(hsp->data[(sx+1+sy*16)*3+1]<<8)+(hsp->data[(sx+1+sy*16)*3+2]<<16))==c) HSP_unfill(hsp,sx+1,sy);
	if (sx>0 &&  !hsp->mask[sx-1+sy*16] && (hsp->data[(sx-1+sy*16)*3+0]+(hsp->data[(sx-1+sy*16)*3+1]<<8)+(hsp->data[(sx-1+sy*16)*3+2]<<16))==c) HSP_unfill(hsp,sx-1,sy);
	if (sy<15 && !hsp->mask[sx+sy*16+16] && (hsp->data[(sx+sy*16+16)*3+0]+(hsp->data[(sx+sy*16+16)*3+1]<<8)+(hsp->data[(sx+sy*16+16)*3+2]<<16))==c) HSP_unfill(hsp,sx,sy+1);
	if (sy>0 &&  !hsp->mask[sx+sy*16-16] && (hsp->data[(sx+sy*16-16)*3+0]+(hsp->data[(sx+sy*16-16)*3+1]<<8)+(hsp->data[(sx+sy*16-16)*3+2]<<16))==c) HSP_unfill(hsp,sx,sy-1);
}

/* from tools/library */
void ObjectArrayAddValue(void **zearray, int *nbfields, int *maxfields, void *zeobject, int object_size)
{
        char *dst;

        if ((*zearray)==NULL) {
                *nbfields=1;
                *maxfields=16; // tuning for THIS software
                (*zearray)=malloc((*maxfields)*object_size);
        } else {
                *nbfields=(*nbfields)+1;
                if (*nbfields>=*maxfields) {
                        *maxfields=(*maxfields)*2;
                        (*zearray)=realloc((*zearray),(*maxfields)*object_size);
                }
        }
        dst=((char *)(*zearray))+((*nbfields)-1)*object_size;
        memcpy(dst,zeobject,object_size);
}

/* super cube things */
struct s_color_box
{
	int x,y,z; /* 3D position */
	int w,h,d; /* 3D size */
};

struct s_super_pixel {
	int r,v,b;
};
struct s_super_cell {
	struct s_super_pixel *pixel;
	int nbpixel,maxpixel;
	int reference;
};

/* 
	v1.0
	algo de recherche basé sur la distance entre chaque couleur
	recherche de la première couleur au plus bas du supercube
	palette peut être pré-initialisée
	calculs avec sub-précision due au supercube
*/
int colorz_create_palette(unsigned char *data, int size, unsigned char *palette,int start)
{
	static int farfrom[4096];
	static int first=1;

	int cube[4096]={0};
	int maxcoul,i,j,c,r=0,total,idx;
	/* stats */
	double pseudo_variance[3];
	int population_trigger;
	int split[3];

	int ar,av,ab;
	int imin,imax,nmax;
	double dmax,distance,mindistance;

	/* super cube */
	struct s_super_cell supercube[4096];
	struct s_super_pixel superpixel;
	struct s_super_pixel referencepixel[16];
	int howmany,hsp=0;
	int x,y,z;

	/* préparation du supercube */
	if (start==-1) {
		start=0;
		hsp=1;
	}

	memset(supercube,0,sizeof(supercube));

	maxcoul=start;
	howmany=16-hsp;
	for (i=0;i<start;i++) {
		idx=(palette[i*3+0]>>4)+(palette[i*3+1]>>4)*16+(palette[i*3+2]>>4)*256;
		superpixel.r=palette[i*3+0];
		superpixel.v=palette[i*3+1];
		superpixel.b=palette[i*3+2];
		referencepixel[r++]=superpixel;
		howmany--;
		ObjectArrayAddValue((void **)&supercube[idx].pixel,&supercube[idx].nbpixel,&supercube[idx].maxpixel,&superpixel,sizeof(struct s_super_pixel));
	}

	/* construction du super cube */
	for (i=0;i<size;i++) {
		idx=(data[i*3+0]>>4)+(data[i*3+1]>>4)*16+(data[i*3+2]>>4)*256;
		superpixel.r=data[i*3+0];
		superpixel.v=data[i*3+1];
		superpixel.b=data[i*3+2];
		ObjectArrayAddValue((void **)&supercube[idx].pixel,&supercube[idx].nbpixel,&supercube[idx].maxpixel,&superpixel,sizeof(struct s_super_pixel));
		/* on ne compte que le premier point */
		if (supercube[idx].nbpixel==1) maxcoul++;
	}
	/* pour chaque point du super cube on sait combien on a d'occurences */

	if (maxcoul<16-hsp) {
		/* full "almost exact" colorz */
		r=0;
		for (i=0;i<4096;i++) {
			if (supercube[i].nbpixel) referencepixel[r++]=supercube[i].pixel[0]; // service minimum
		}
	} else {
		/***********************************************
		     c o l o r   a p p r o x i m a t i o n
		***********************************************/

		/* on prend la première couleur du supercube qui est la plus éloignée du centre! */
		for (i=0;i<4096;i++) if (supercube[i].nbpixel) break;
		/* à cet endroit on peut arriver avec des références pré-établies et ne chercher que d'autres couleurs :) */

		if (!r) {
			referencepixel[0]=supercube[i].pixel[0];howmany--;r=1;
		}
		while (howmany) {
			/* tant qu'il nous reste des couleurs de référence disponibles */
			imax=-1;nmax=0;dmax=-1;
			/* on parcourt notre tableau */
			for (i=0;i<4096;i++) {
				for (j=0;j<supercube[i].nbpixel;j++) {
					mindistance=65536*3;
					/* on compare la couleur courante avec toutes les références! */
					for (c=0;c<r;c++) {
						distance=(supercube[i].pixel[j].r-referencepixel[c].r)*(supercube[i].pixel[j].r-referencepixel[c].r)+
							(supercube[i].pixel[j].v-referencepixel[c].v)*(supercube[i].pixel[j].v-referencepixel[c].v)+
							(supercube[i].pixel[j].b-referencepixel[c].b)*(supercube[i].pixel[j].b-referencepixel[c].b);
						if (distance<mindistance) mindistance=distance;
					}
					if (mindistance>dmax) {
						/* on se garde l'index sous le coude si elle est plus éloignée que les autres */
						dmax=mindistance;
						imax=i;
						nmax=j;
					}
				}
			}
			/* nouvelle référence */
			if (imax>=0) referencepixel[r]=supercube[imax].pixel[nmax]; else {printf("internal error: imax MUST find a color\n");exit(-1);}
			howmany--;
			r++;
		}

//for (i=0;i<r;i++) printf("reference[%02d]=(%02X/%02X/%02X)\n",i,referencepixel[i].r,referencepixel[i].b,referencepixel[i].v);

		/* on donne aux couleurs restantes une référence par défaut */
		for (i=0;i<4096;i++) {
			if (supercube[i].reference==-1) {
				/* on compare la couleur courante avec toutes les références! */
				j=imin=0;
				mindistance=65536*3;
				for (c=0;c<r;c++) {
					distance=(supercube[i].pixel[j].r-referencepixel[c].r)*(supercube[i].pixel[j].r-referencepixel[c].r)+
						(supercube[i].pixel[j].v-referencepixel[c].v)*(supercube[i].pixel[j].v-referencepixel[c].v)+
						(supercube[i].pixel[j].b-referencepixel[c].b)*(supercube[i].pixel[j].b-referencepixel[c].b);
					if (distance<mindistance) {
						mindistance=distance;
						imin=c;
					}
				}
				supercube[i].reference=imin;
			}
		}

	}
	for (i=0;i<r;i++) {
		palette[i*3+0]=referencepixel[i].r&0xF0;
		palette[i*3+1]=referencepixel[i].v&0xF0;
		palette[i*3+2]=referencepixel[i].b&0xF0;
	}

	for (i=0;i<4096;i++) {
		if (supercube[i].pixel) free(supercube[i].pixel);
	}
	return r;
}



int __GetIDXFromPalette(unsigned char *palette, int r, int v, int b,int maxcoul)
{
	#undef FUNC
	#define FUNC "GetIDXFromPalette"

	int imin,vmin,va;
	int i;

	if (r<0) r=0; else if (r>255) r=255;
	if (v<0) v=0; else if (v>255) v=255;
	if (b<0) b=0; else if (b>255) b=255;

	for (i=0;i<maxcoul;i++) {
		if (palette[i*3+0]==r && palette[i*3+1]==v && palette[i*3+2]==b) return i;
	}
	vmin=65536*32;
	imin=0;
	for (i=0;i<maxcoul;i++) {
		va=((int)palette[i*3+0]-r)*((int)palette[i*3+0]-r)+((int)palette[i*3+1]-v)*((int)palette[i*3+1]-v)+((int)palette[i*3+2]-b)*((int)palette[i*3+2]-b);
		if (va<vmin) {
			vmin=va;
			imin=i;
		}
	}
	//logwarn("palette is approximative regarding the datas... RVB:%X%02X%02X -> %X%02X%02X",r,v,b,palette[imin*3+0],palette[imin*3+1],palette[imin*3+2]);
	return imin;
}
int GetIDXFromPalette(unsigned char *palette, int r, int v, int b) {
	return __GetIDXFromPalette(palette, r,v,b,16);
}


struct s_rastamix {
unsigned int asicad[4]; //asicad1,asicad2,asicad3,asicad4;
unsigned int asicol[4]; //asicol1, asicol2, asicol3, asicol4;
unsigned int hspad;
unsigned int hspcol1,hspcol2;
unsigned char palette[48];
int l;
unsigned char clipped[384]; // HSP index +1 ou zero si rien
int adr;
};



int compare_hsp(const void * a, const void * b)
{
	struct s_hardware_sprite *c,*d;
	int ret;
	
	c=(struct s_hardware_sprite *)a;
	d=(struct s_hardware_sprite *)b;

	/* tri de haut en bas et de gauche à droite */	
	ret=c->y-d->y;
	if (ret) return ret; else return c->x-d->x;
}

int Build(char *filename, int dithering, int uniform)
{
	#undef FUNC
	#define FUNC "Build"

enum e_module {
	E_MODULE_QUANTIZATION=0,
	E_MODULE_PALETTE,
	E_MODULE_EDITION
};

	enum e_module current_module=E_MODULE_QUANTIZATION;

	/* libSDL2 */
        SDL_Window *win=NULL;
        SDL_Surface *surface=NULL,*screen;
        int *pixels,ok=1,gmx,gmy,ms;
        const unsigned char *state;
	unsigned int *membitmap;
	int nokey=0;

	#define BLACK_COLOR 0xFF000000;
	unsigned int myblack=BLACK_COLOR;
	#define GREEN_COLOR 0xFF00FF00;
	unsigned int mygreen=GREEN_COLOR;
	#define CYAN_COLOR 0xFFFF8888;
	unsigned int mycyan=CYAN_COLOR;


	unsigned int myg=GREEN_COLOR;
	#define RED_COLOR 0xFF0000FF;
	unsigned int myr=RED_COLOR;
	#define BLUE_COLOR 0xFFFF0000;
	unsigned int myb=BLUE_COLOR;

	#define VIOLET_COLOR 0xFFFF1080
	unsigned int myviolet=VIOLET_COLOR;
	#define GREY_COLOR 0xFF777777
	unsigned int mygrey=GREY_COLOR;
	#define WHITE_COLOR 0xFFFFFFFF
	unsigned int mywhite=WHITE_COLOR;


	int winx,winy;
	int redo=2,redraw=1,reset=1;
	/*-----------*/
	struct s_png_info *photo;
	struct s_raw_info rawinfo={0};
	int i,j,l,m,n,v;
	int *cptpalette;
	int width,height;
	float vmin,vmax,vpal,totpal;
	int ligne[192],adr,adrcode,numligne;
	unsigned char cpc[65536]={0};
	char cpccode[65536]={0};

	unsigned char refpalette[16*3];
	unsigned char tmppalette[16*3];
	int checkipal[16];
	int checknewpal[16];
	int cptnewpal[16];
	int cptrefpal[16];
	int newcoloridx[4],newcolorpush;
	int iref;
	/*--------------------*/
	char sprfilename[PATH_MAX];
	char asmfilename[PATH_MAX];
	char cprasmfilename[PATH_MAX];
	char scrfilename1[PATH_MAX];
	char scrfilename2[PATH_MAX];
	char xmlfilename[PATH_MAX];
	char previewfilename[PATH_MAX];
	/*--------------------*/
	struct s_xml_field *resource=NULL;
	struct s_xml_field *xmlhsp=NULL,*xmlhsptab=NULL,*xmlparam=NULL,*xmlrasta=NULL,*xmlrastatab=NULL;
	unsigned char *data,*preview;
	int x,y,down=0,downspace=0,mx,my,sx,sy;
	struct s_hardware_sprite hsp[16]={0};
	int nbhsp=0,curhsp=0;
	struct s_rastamix *rastamix=NULL;
	unsigned int asicolinit[32]={0};
	int group,igroup;
	int toggle_greentea=1;
	int c,compute=0,computeimage=0;
	int omx,omy,rm,vm,bm,cm,lasty,lastsp,previouslasty;

	/* v3 */
	float floydcoef=0.3;
	float sharpnesscoef=0.0;
	float contrastcoef=0.0;
	/* v5 */
	int leveldown=0;
	int levelup=255;
	int reboot,k,computeglobal=1;
	int imin,imax,icol,ipal,idark1,idark2;
	int tic,pr,pv,pb,pix1,pix2,zepix;
	int asicad;
	int clipcol[16];
	int artefacts,artebis,wasmoving=0;
	int maskvalue=-1;
	/* v7 */
	int legacy_display=1;
	int nopfirst;
	/* v8 */
	int refgmx,refgmy,cumulgmx,cumulgmy;
	int hspset_display=0,locked=0;
	int keycursorx=0,keycursory=0;
	int currentpen=5;
	/* ergo */
	int touchfloyd=0, touchsharp=0, touchcontrast=0, touchlevel=0, touchmask=0;

	strcpy(sprfilename,filename);
	TxtReplace(sprfilename,".png",".spr",0);
	strcpy(xmlfilename,filename);
	TxtReplace(xmlfilename,".png",".xml",0);
	sprintf(cprasmfilename,"%scpr",filename);
	TxtReplace(cprasmfilename,".pngcpr","cpr.asm",0);
	sprintf(previewfilename,"%spreview",filename);
	TxtReplace(previewfilename,".pngpreview","preview.png",0);
	strcpy(asmfilename,filename);
	TxtReplace(asmfilename,".png",".asm",0);
	strcpy(scrfilename1,filename);
	TxtReplace(scrfilename1,".png",".sc1",0);
	strcpy(scrfilename2,filename);
	TxtReplace(scrfilename2,".png",".sc2",0);

        photo=PNGRead24(filename);
        if (!photo) logerr("ERR");
        loginfo("PNG image is %dx%dx%d",photo->width,photo->height,photo->bit_depth);
        if (photo->color_type!=PNG_COLOR_TYPE_RGB) {
                logerr("PNG image must be RGB without transparency",filename);
                exit(ABORT_ERROR);
        }
        if (photo->width!=384 || photo->height>273 || photo->height<16) {
				float xmul;
				int newypict=272;
				if (photo->width!=384) logwarn("PNG file [%s] is not 384 pixels width",filename);
				if (photo->height>273) logwarn("PNG file [%s] more than 273 pixels height",filename);
				if (photo->width!=384) {
					xmul=384.0/(float)photo->width;
					newypict=photo->height*xmul;
					if (newypict>273) newypict=273; // et tant pis pour le ratio!
				}
                photo->data=ImageReduction(photo->data,photo->width,photo->height,384,newypict);
                photo->width=384;
                photo->height=newypict;
        }

	/* on alloue le max */
	data=MemMalloc(384*273*3);
	preview=MemCalloc(384*273*3);
	/* data est la REFERENCE ultime */
	memcpy(data,photo->data,384*photo->height*3);

	rastamix=MemCalloc(sizeof(struct s_rastamix)*273);

	if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
			fprintf(stderr,"SDL_Init error\n");
			return -1;
	}
	loginfo("SDL_Init");
	winx=(384+256)*2;
	winy=273*2+1;

	if ((win=SDL_CreateWindow(WINDOW_NAME, 30, 30, winx, winy, SDL_WINDOW_SHOWN))==NULL) {
			fprintf(stderr,"SDL_CreateWindow error\n");
			return -1;
	}
	SDL_SetWindowPosition(win,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
	screen=SDL_GetWindowSurface(win);
	if ((surface=SDL_CreateRGBSurface(0,winx,winy,32,0,0,0,0))==NULL) { // default mask for 32 bits pixels
			fprintf(stderr,"SDL_CreateRGBSurface error\n");
			return -1;
	}

	width=photo->width;
	height=photo->height;

	curhsp=nbhsp=0;
	if (FileExists(xmlfilename)) {
		unsigned char *zemask;
		unsigned char *zedata;
		int tmpheight;
		resource=XMLLoadFile(xmlfilename);
		//XMLDumpTree(resource);
		
		if ((xmlparam=XMLGetField(resource,"height"))!=NULL) tmpheight=atoi(XMLGetFieldAttrValueFromField(xmlparam,"v"));
		if (height!=photo->height) {
			XMLFreeField(resource);
			logerr("XML loaded but not applied because declared height is different from current picture!\n");
		} else {
			if ((xmlparam=XMLGetField(resource,"locked"))!=NULL) locked=atoi(XMLGetFieldAttrValueFromField(xmlparam,"v"));
			if (locked) {
				current_module=E_MODULE_EDITION;
			} else {
				if ((xmlparam=XMLGetField(resource,"module"))!=NULL) current_module=atoi(XMLGetFieldAttrValueFromField(xmlparam,"v"));
				switch (current_module) {
					case E_MODULE_EDITION:
					case E_MODULE_PALETTE:locked=1; // temporaire
						break;
					case E_MODULE_QUANTIZATION:
						locked=0;
						break;
				}
			}
			if ((xmlparam=XMLGetField(resource,"keycursorx"))!=NULL) keycursorx=atoi(XMLGetFieldAttrValueFromField(xmlparam,"v"));
			if ((xmlparam=XMLGetField(resource,"keycursory"))!=NULL) keycursory=atoi(XMLGetFieldAttrValueFromField(xmlparam,"v"));
			if ((xmlparam=XMLGetField(resource,"floyd"))!=NULL) floydcoef=atof(XMLGetFieldAttrValueFromField(xmlparam,"v"));
			if ((xmlparam=XMLGetField(resource,"sharp"))!=NULL) sharpnesscoef=atof(XMLGetFieldAttrValueFromField(xmlparam,"v"));
			if ((xmlparam=XMLGetField(resource,"contrast"))!=NULL) contrastcoef=atof(XMLGetFieldAttrValueFromField(xmlparam,"v"));
			if ((xmlparam=XMLGetField(resource,"levelup"))!=NULL) levelup=atoi(XMLGetFieldAttrValueFromField(xmlparam,"v"));
			if ((xmlparam=XMLGetField(resource,"leveldown"))!=NULL) leveldown=atoi(XMLGetFieldAttrValueFromField(xmlparam,"v"));

			if ((xmlhsp=XMLGetField(resource,"sprites"))!=NULL) {
				xmlhsptab=XMLGetFieldMulti(xmlhsp,"sprite",&nbhsp);
				for (i=0;i<nbhsp;i++) {
					hsp[i].x=atoi(XMLGetFieldAttrValueFromField(&xmlhsptab[i],"x"));
					hsp[i].y=atoi(XMLGetFieldAttrValueFromField(&xmlhsptab[i],"y"));
					hsp[i].group=atoi(XMLGetFieldAttrValueFromField(&xmlhsptab[i],"group"));
					
					/* on récupère aussi la palette */
					for (j=0;j<45;j++) {
						char bufname[128];
						sprintf(bufname,"p%02d",j);
						hsp[i].palette[j]=atoi(XMLGetFieldAttrValueFromField(&xmlhsptab[i],bufname));
					}
					
					/* recup du masque */
					zemask=XMLGetFieldValue(&xmlhsptab[i],"mask");
					if (zemask && strlen(zemask)>=256) {
						for (l=0;l<256;l++) {
							hsp[i].mask[l]=zemask[l]-'0';
						}
					} else {
						printf("WARNING: no MASK for HSP %d in XML\n",i);
					}
					for (l=0;l<256;l++) {
						if (hsp[i].mask[l]) hsp[i].mask[l]=1;
					}
					/* recup des DATA si présentes et mode locked */
					if (locked) {
						zedata=XMLGetFieldValue(&xmlhsptab[i],"data");
						if (zedata && strlen(zedata)>=768*2) {
							for (l=0;l<768;l++) {
								if (zedata[l*2+0]<='9' && zedata[l*2+0]>='0') 
									hsp[i].data[l]=zedata[l*2+0]-'0';
								else
									hsp[i].data[l]=zedata[l*2+0]-'A'+10;
								hsp[i].data[l]<<=4;
								if (zedata[l*2+1]<='9' && zedata[l*2+1]>='0') 
									hsp[i].data[l]+=zedata[l*2+1]-'0';
								else
									hsp[i].data[l]+=zedata[l*2+1]-'A'+10;
							}
						} else {
							printf("WARNING: no DATA for HSP %d in XML\n",i);
						}
					}
				}
			}
			
			if (locked) {
				loginfo("Loading back rastamix structs");
				if ((xmlparam=XMLGetField(resource,"rastainit"))!=NULL) {
					char buftmp[256];
					for (l=0;l<31;l++) {
						sprintf(buftmp,"asicolinit%02d",l);
						asicolinit[l]=atoi(XMLGetFieldAttrValueFromField(xmlparam,buftmp));
					}
				} else {
					logerr("XML corrupted no init colors!\n");
					exit(-2);
				}


				if ((xmlrasta=XMLGetField(resource,"rastamixtab"))!=NULL) {
					char buftmp[256];
					int nbrasta;
					
					xmlrastatab=XMLGetFieldMulti(xmlrasta,"rastamix",&nbrasta);
					if (!xmlrastatab || nbrasta!=height) {
						XMLFreeField(resource);
						printf("XML corrupted (rastamix)!\n");
						exit(-1);
					}
					
					for (i=0;i<nbrasta;i++) {
						rastamix[i].adr=atoi(XMLGetFieldAttrValueFromField(&xmlrastatab[i],"adr"));
						rastamix[i].hspad=atoi(XMLGetFieldAttrValueFromField(&xmlrastatab[i],"hspad"));
						rastamix[i].hspcol1=atoi(XMLGetFieldAttrValueFromField(&xmlrastatab[i],"hspcol1"));
						rastamix[i].hspcol2=atoi(XMLGetFieldAttrValueFromField(&xmlrastatab[i],"hspcol2"));
						rastamix[i].l=atoi(XMLGetFieldAttrValueFromField(&xmlrastatab[i],"l"));
						
						for (l=0;l<4;l++) {
							sprintf(buftmp,"asicad%02d",l);
							rastamix[i].asicad[l]=atoi(XMLGetFieldAttrValueFromField(&xmlrastatab[i],buftmp));
							if (i>1 && (rastamix[i].asicad[l]<0x6400 || rastamix[i].asicad[l]>0x641F)) {
								printf("XML corrupted rastaline %d asicoladr[%d]=%X\n",i,l,rastamix[i].asicad[l]);
								exit(-2);
							}
							sprintf(buftmp,"asicol%02d",l);
							rastamix[i].asicol[l]=atoi(XMLGetFieldAttrValueFromField(&xmlrastatab[i],buftmp));
						}
						for (l=0;l<48;l++) {
							sprintf(buftmp,"p%02d",l);
							rastamix[i].palette[l]=atoi(XMLGetFieldAttrValueFromField(&xmlrastatab[i],buftmp));
						}
						
						memset(rastamix[i].clipped,0,sizeof(rastamix[i].clipped));
					}
				}

				/* reconstruction des infos de clipping à partir des masques */
				for (i=nbhsp-1;i>=0;i--) {
					l=0;
					for (y=0;y<16;y++)
					for (x=0;x<16;x++) {
						if (hsp[i].mask[l]) {
							rastamix[hsp[i].y+y].clipped[hsp[i].x+x]=i+1; // index du sprite+1 dans les infos de clipping
						}
						l++;
					}
				}
				
				loginfo("Loading back preview");
				zedata=XMLGetFieldValue(resource,"preview");
				if (zedata && strlen(zedata)>=384*3*2*photo->height) {
					for (l=0;l<384*3*photo->height;l++) {
						if (zedata[l*2+0]<='9' && zedata[l*2+0]>='0') 
							preview[l]=zedata[l*2+0]-'0';
						else
							preview[l]=zedata[l*2+0]-'A'+10;
						preview[l]<<=4;
						if (zedata[l*2+1]<='9' && zedata[l*2+1]>='0') 
							preview[l]+=zedata[l*2+1]-'0';
						else
							preview[l]+=zedata[l*2+1]-'A'+10;
					}
				} else {
					printf("XML preview corrupted\n");
					exit(-2);
				}
				
				loginfo("Loading back cpcdata");
				zedata=XMLGetFieldValue(resource,"cpcdata");
				if (zedata && strlen(zedata)>=65536) {
					for (l=0;l<32768;l++) {
						if (zedata[l*2+0]<='9' && zedata[l*2+0]>='0') 
							cpc[l]=zedata[l*2+0]-'0';
						else
							cpc[l]=zedata[l*2+0]-'A'+10;
						cpc[l]<<=4;
						if (zedata[l*2+1]<='9' && zedata[l*2+1]>='0') 
							cpc[l]+=zedata[l*2+1]-'0';
						else
							cpc[l]+=zedata[l*2+1]-'A'+10;
					}
				} else {
					printf("XML cpc data corrupted\n");
					exit(-2);
				}
				MemFree(xmlrastatab);
			}
		}
		MemFree(xmlhsptab);
		XMLFreeField(resource);
		loginfo("XML loaded");
	}
	omx=-1;omy=-1;

	while (redo) {
		if (!locked) {
			if (reset) {
				reset=0;
				redraw=1;
				compute=1;
				computeimage=1;
				for (i=0;i<nbhsp;i++) {
				l=0;
				for (y=hsp[i].y;y<hsp[i].y+16;y++)
				for (x=hsp[i].x;x<hsp[i].x+16;x++) {
					hsp[i].data[l++]=data[(y*width+x)*3+0];
					hsp[i].data[l++]=data[(y*width+x)*3+1];
					hsp[i].data[l++]=data[(y*width+x)*3+2];
				}
				}
			}
			/************************************ compute GFX colorz ***********************************/
			if (computeglobal) {
				unsigned char *newpix;
				computeglobal=0;
				/* reset data */
				memcpy(photo->data,data,384*photo->height*3);

				if (sharpnesscoef>0.1) {
					newpix=ImageSharpness(photo->data,384,photo->height,sharpnesscoef*20);
					MemFree(photo->data);
					photo->data=newpix;
				}
				if (contrastcoef>0.1) {
					newpix=ImageContrast(photo->data,384,photo->height,contrastcoef*20);
					MemFree(photo->data);
					photo->data=newpix;
				}
				if (leveldown>3 || levelup<252) {
					newpix=ImageLevel(photo->data,384,photo->height,leveldown,levelup);
					MemFree(photo->data);
					photo->data=newpix;
				}
				compute=1;
			}
			if (computeimage || compute) {
				float scanfloyd[192*3*2];
				float or,ov,ob,qr,qv,qb;
				unsigned char scanline[192*3*2];
				unsigned char clippedscanline[192*3*2];
				int cr,cv,cb,sizeclip;
				int refl,ihsp,imaskhsp,xhsp,flagclip;
				computeimage=0;
				compute=0;
				adr=numligne=0; // amstrad memory

				/********************************************************
						  c o m p u t e   H S P   c o l o r s
				********************************************************/
				/* reset mask positions & hsp raster infos */
				for (i=0;i<photo->height;i++) {
					memset(rastamix[i].clipped,0,sizeof(rastamix[i].clipped));
					rastamix[i].hspad=0;
					rastamix[i].hspcol1=0;
					rastamix[i].hspcol2=0;

				}

				/* on met à jour quel sprite est actif avant de les réordonner */
				for (i=0;i<nbhsp;i++) hsp[i].active=0; hsp[curhsp].active=1;

				/* on réordonne les sprites dans l'ordre d'affichage de haut en bas ET gauche à droite */
				qsort(hsp,nbhsp,sizeof(struct s_hardware_sprite),compare_hsp);

				/* on récupère l'index du sprite actif pour ne pas que l'éditeur se perde */
				for (i=0;i<nbhsp;i++) {
					if (hsp[i].active) {
						curhsp=i;
						if (wasmoving) wasmoving=1+curhsp;
					}
				}

				/* on découpe en groupes selon l'espacement vertical entre les sprites hards */
				group=0;
				hsp[0].group=group; /* fix premier sprite noir à l'init */
				for (i=1;i<nbhsp;i++) {
					if (hsp[i-1].y+16+8<hsp[i].y) {
						group++;
					}
					hsp[i].group=group;
				}
				/* reduce color for each group */
				for (igroup=0;igroup<=group;igroup++) {
					float floydHSP[18*18];
					int bunchidx;
					int startx,endx,starty,endy;

					/* on alloc le max théorique */
					rawinfo.data=MemMalloc(256*16*3);

					/* make a bunch of pixels to compute colorz  */
					bunchidx=0;
					for (i=0;i<nbhsp;i++) {
						if (hsp[i].group==igroup) {
							l=0;
							for (y=0;y<16;y++)
							for (x=0;x<16;x++) {
								if (hsp[i].mask[l]) {
									rawinfo.data[bunchidx+0]=photo->data[(hsp[i].x+x+(hsp[i].y+y)*384)*3+0];
									rawinfo.data[bunchidx+1]=photo->data[(hsp[i].x+x+(hsp[i].y+y)*384)*3+1];
									rawinfo.data[bunchidx+2]=photo->data[(hsp[i].x+x+(hsp[i].y+y)*384)*3+2];
									bunchidx+=3;
								}
								l++;
							}
						}
					}
					/* on calcule la palette sur le groupe */
					if (bunchidx) {
						rawinfo.nbcolor=colorz_create_palette(rawinfo.data,bunchidx/3,tmppalette,-1); // -1 means 16-1 -> 15 colorz MAX
					} else {
						rawinfo.nbcolor=0;
					}
					/* fill unused colors with zeros */
					while (rawinfo.nbcolor<15) {
						tmppalette[rawinfo.nbcolor*3+0]=0;
						tmppalette[rawinfo.nbcolor*3+1]=0; 
						tmppalette[rawinfo.nbcolor*3+2]=0;
						rawinfo.nbcolor++;
					}
					/* on met à jour le clipped mask de l'écran */
					for (i=nbhsp-1;i>=0;i--) {
						if (hsp[i].group==igroup) {
							memcpy(hsp[i].palette,tmppalette,sizeof(tmppalette));
							lasty=hsp[i].y+16;
							lastsp=i;
						}
						l=0;
						for (y=0;y<16;y++)
						for (x=0;x<16;x++) {
							if (hsp[i].mask[l]) {
								rastamix[hsp[i].y+y].clipped[hsp[i].x+x]=i+1; // index du sprite+1 dans les infos de clipping
							}
							l++;
						}
					}
					lastsp=0;

					if (igroup==0) {
						/* first group colors initialised outside rastamix */
						x=0;
						for (j=16;j<31;j++) {
							asicolinit[j]=((hsp[lastsp].palette[x*3+1]>>4)<<8)|(hsp[lastsp].palette[x*3+0]&0xF0)|((hsp[lastsp].palette[x*3+2]>>4)&0xF);
							x++;
						}
					} else {
						/* insert colors in rastamix */
						asicad=0x6422;
						x=0;
						for (j=previouslasty;j<previouslasty+8;j++) {
							rastamix[j].hspad=asicad;
							asicad+=4;
							rastamix[j].hspcol1=((hsp[lastsp].palette[x*3+1]>>4)<<8)|(hsp[lastsp].palette[x*3+0]&0xF0)|((hsp[lastsp].palette[x*3+2]>>4)&0xF);
							x++;
							rastamix[j].hspcol2=((hsp[lastsp].palette[x*3+1]>>4)<<8)|(hsp[lastsp].palette[x*3+0]&0xF0)|((hsp[lastsp].palette[x*3+2]>>4)&0xF);
							x++;
						}
					}
					previouslasty=lasty;
					ImageRAWFreeStruct(&rawinfo);
				}

				/*************************************************************************************************************
				**************************************************************************************************************


							C A L C U L     D E S     P A L E T T E S    P O U R     T O U T     L ' E C R A N


				**************************************************************************************************************
				*************************************************************************************************************/

				/****************************************************************************
					t r a v a i l   s u r   l e s    2    p r e m i è r e s    l i g n e s
				****************************************************************************/
				for (j=0;j<192*2;j++) {
					scanline[j*3+0]=(photo->data[j*6+0]+photo->data[j*6+3])*0.5;
					scanline[j*3+1]=(photo->data[j*6+1]+photo->data[j*6+4])*0.5;
					scanline[j*3+2]=(photo->data[j*6+2]+photo->data[j*6+5])*0.5;
				}
				/*****************************************************************
					   on élimine les données cachées par les sprites hard
				*****************************************************************/
				sizeclip=0;
				for (j=0;j<192;j++) {
					if (!rastamix[0].clipped[j*2] || !rastamix[0].clipped[j*2+1]) {
						clippedscanline[sizeclip*3+0]=scanline[j*3+0];
						clippedscanline[sizeclip*3+1]=scanline[j*3+1];
						clippedscanline[sizeclip*3+2]=scanline[j*3+2];
						sizeclip++;
					}
					if (!rastamix[1].clipped[j*2] || !rastamix[1].clipped[j*2+1]) {
						clippedscanline[sizeclip*3+0]=scanline[j*3+0+192*3];
						clippedscanline[sizeclip*3+1]=scanline[j*3+1+192*3];
						clippedscanline[sizeclip*3+2]=scanline[j*3+2+192*3];
						sizeclip++;
					}
				}

				/* palette commune aux deux premières lignes */
				refl=rastamix[0].l=colorz_create_palette(clippedscanline,sizeclip,rastamix[0].palette,0);
				rastamix[1].l=refl;
				memcpy(rastamix[1].palette,rastamix[0].palette,sizeof(rastamix[0].palette));

				/****************************************************************************************
						  l i g n e s     s u i v a n t e s . . .
				****************************************************************************************/
				reboot=0;
				for (i=2;i<photo->height;i++) {
					/* on utilise systématiquement les données de clipping pour constuire la clippedscan line */
					sizeclip=0;
					for (j=0;j<192;j++) {
						/* on fait des pixels mode 0 à partir d'une résolution type mode 1 high color */
						scanline[j*3+0]=(photo->data[j*6+0+i*384*3]+photo->data[j*6+3+i*384*3])*0.5;
						scanline[j*3+1]=(photo->data[j*6+1+i*384*3]+photo->data[j*6+4+i*384*3])*0.5;
						scanline[j*3+2]=(photo->data[j*6+2+i*384*3]+photo->data[j*6+5+i*384*3])*0.5;
						if (!rastamix[i].clipped[j*2] || !rastamix[i].clipped[j*2+1]) {
							clippedscanline[sizeclip*3+0]=scanline[j*3+0];
							clippedscanline[sizeclip*3+1]=scanline[j*3+1];
							clippedscanline[sizeclip*3+2]=scanline[j*3+2];
							sizeclip++;
						}
					}

					/****************************************************************************************
						 on fait une première passe pour avoir une palette complète dès la première ligne
					****************************************************************************************/
					if (refl<16) {
						/* on calcule une palette complète pour la ligne */
						l=colorz_create_palette(clippedscanline,sizeclip,tmppalette,0);

						for (j=0;j<l && !reboot;j++) {
							for (k=0;k<refl;k++) {
								if (rastamix[0].palette[k*3+0]==tmppalette[j*3+0] && 
									rastamix[0].palette[k*3+1]==tmppalette[j*3+1] &&
									rastamix[0].palette[k*3+2]==tmppalette[j*3+2])
									break;
							}
							/* c'est une nouvelle couleur */
							if (k<refl) {
								rastamix[0].palette[refl*3+0]=tmppalette[j*3+0];
								rastamix[0].palette[refl*3+1]=tmppalette[j*3+1];
								rastamix[0].palette[refl*3+2]=tmppalette[j*3+2];
								refl++;
								/* maj de la ligne 1 */
								rastamix[1].l=refl;
								memcpy(rastamix[1].palette,rastamix[0].palette,48);
								if (refl==16) {
									reboot=1;
								}
							}
						}
						if (reboot) {
							i=1;
							continue;
						}
					}
					/****************************************************************************************
												A F T E R        R E B O O T
					****************************************************************************************/

					/* on s'fait pas chier, on garde les 12 couleurs les plus utilisées avec la palette de la ligne précédente */
					memset(cptrefpal,0,sizeof(cptrefpal));
					for (j=0;j<sizeclip;j++) {
						c=__GetIDXFromPalette(rastamix[i-1].palette,clippedscanline[j*3+0],clippedscanline[j*3+1],clippedscanline[j*3+2],rastamix[i-1].l);
						cptrefpal[c]++;
					}
					memcpy(tmppalette,rastamix[i-1].palette,sizeof(tmppalette));
					l=rastamix[i-1].l;

					/* pas besoin de virer des couleurs si on a déjà moins de 12 couleurs... */
					for (k=0;k<rastamix[i-1].l-12;k++) {
						vmin=193;
						for (j=0;j<l;j++) {
							if (cptrefpal[j]<vmin) {
								vmin=cptrefpal[j];
								imin=j;
							}
						}
						l--;
						tmppalette[imin*3+0]=tmppalette[l*3+0];
						tmppalette[imin*3+1]=tmppalette[l*3+1];
						tmppalette[imin*3+2]=tmppalette[l*3+2];
						cptrefpal[imin]=cptrefpal[l];
					}
				
					/* on demande une palette pour la ligne courante avec 12 pré-sélections */	
					rastamix[i].l=colorz_create_palette(clippedscanline,sizeclip,tmppalette,l);
					memcpy(rastamix[i].palette,tmppalette,sizeof(tmppalette));
				}

				/*************************************************************************************************************
				**************************************************************************************************************

											   C O N V E R S I O N    D E S    P I X E L S

				**************************************************************************************************************
				*************************************************************************************************************/


				/* initialisation du buffer de précision pour le floyd steinberg */
				for (i=0;i<2;i++) {
					for (j=0;j<192;j++) {
						scanfloyd[j*3+0+i*192*3]=(photo->data[j*6+0+i*384*3]+photo->data[j*6+3+i*384*3])*0.5;
						scanfloyd[j*3+1+i*192*3]=(photo->data[j*6+1+i*384*3]+photo->data[j*6+4+i*384*3])*0.5;
						scanfloyd[j*3+2+i*192*3]=(photo->data[j*6+2+i*384*3]+photo->data[j*6+5+i*384*3])*0.5;
					}
				}

				/*******************************************************************************************************
				********************************************************************************************************
				
				           T R A V A I L    G E N E R A L    S U R    T O U T E S    L E S    L  I G N E S
						   
				********************************************************************************************************
				*******************************************************************************************************/

				for (i=0;i<photo->height;i++) {
					
					/* on conserve l'adresse de début de ligne pour travailler plus facilement dans l'éditeur */
					rastamix[i].adr=adr;
					
					/************************************************************
						  réutilisation de la palette précédente au maximum
					************************************************************/
					if (i>1) {
						/* il faut que la palette suivante se calque sur la précédente en termes d'indices de couleurs identiques */
						memset(checkipal,0,sizeof(checkipal));
						memset(checknewpal,0,sizeof(checknewpal));
						/* on copie tout, on écrasera les 4 entrées désuètes après */
						memcpy(refpalette,rastamix[i-1].palette,sizeof(refpalette));

	#if 0
						printf("ligne %d ========================================\n",i);
						for (j=0;j<16;j++) {
							printf("#%02X%02X%02X   #%02X%02X%02X\n",
								rastamix[i-1].palette[j*3+0],rastamix[i-1].palette[j*3+1],rastamix[i-1].palette[j*3+2],
								rastamix[i].palette[j*3+0],rastamix[i].palette[j*3+1],rastamix[i].palette[j*3+2]);
						}
						printf("working...\n");
	#endif
						for (j=0;j<16;j++) {
							for (k=0;k<16;k++) {
								if (!checkipal[k]) /* fix doublon de couleur sur palette de référence! */
								if (rastamix[i].palette[j*3+0]==refpalette[k*3+0])
								if (rastamix[i].palette[j*3+1]==refpalette[k*3+1])
								if (rastamix[i].palette[j*3+2]==refpalette[k*3+2]) {
									/* la palette de référence se calque sur la ligne PRECEDENTE! */
									checkipal[k]=1;   // on check l'index K comme reference occupée
									checknewpal[j]=1; // index J sur la nouvelle ligne
									break;
								}
							}
						}

						/* qu'il reste des couleurs à transférer ou pas, on a besoin de 4 split-rasters! */
						for (l=0;l<4;l++) {
							/* trouve la destination libre J dans la référence */
							j=0;
							while (j<16 && checkipal[j]) j++;
							if (j<16) {
								/* trouve la source dans la palette de la ligne courante */
								for (k=0;k<16 && checknewpal[k];k++);
								if (k>=16) {
									printf("FATAL -> have to fix this!\n");
									exit(-4);
								}
								/* copie la nouvelle couleur vers la référence au bon index! */
	//printf("%d %d ",j,k);fflush(stdout);
								refpalette[j*3+0]=rastamix[i].palette[k*3+0];
								refpalette[j*3+1]=rastamix[i].palette[k*3+1];
								refpalette[j*3+2]=rastamix[i].palette[k*3+2];
								checkipal[j]=1;
								checknewpal[k]=1;
								/* on enregistre les infos de changement de couleur pour la génération de code */
								rastamix[i].asicad[l]=0x6400+j*2; // index libre dans la référence
								rastamix[i].asicol[l]=((refpalette[j*3+1]>>4)<<8)|(refpalette[j*3+0]&0xF0)|((refpalette[j*3+2]>>4)&0xF); // nouvelle couleur dans la nouvelle ligne, évidemment!
							} else {
								while (l<4) {
									/* filler avec la couleur 0 inchangée */
									rastamix[i].asicad[l]=0x6400;
									rastamix[i].asicol[l]=((refpalette[1]>>4)<<8)|(refpalette[0]&0xF0)|((refpalette[2]>>4)&0xF);
									l++;
								}
								break;
							}
						}
						/* ré-écriture de la palette dédiée à la ligne */
						memcpy(rastamix[i].palette,refpalette,sizeof(refpalette));
	#if 0
						for (j=0;j<16;j++) {
							printf("#%02X%02X%02X   #%02X%02X%02X\n",
								rastamix[i-1].palette[j*3+0],rastamix[i-1].palette[j*3+1],rastamix[i-1].palette[j*3+2],
								rastamix[i].palette[j*3+0],rastamix[i].palette[j*3+1],rastamix[i].palette[j*3+2]);
						}
						printf("done\n");
	#endif
					} else if (!i) {
						for (j=0;j<16;j++) {
							/* couleurs d'init */
							asicolinit[j]=((rastamix[i].palette[j*3+1]>>4)<<8)|(rastamix[i].palette[j*3+0]&0xF0)|((rastamix[i].palette[j*3+2]>>4)&0xF);
						}
					}

					/* se mettre la précision du CPC au plus proche */
					for (j=0;j<48;j++) {
						rastamix[i].palette[j]&=0xF0;
					}

					for (j=tic=0;j<192;j++) {
						/* on calcule le pixel écran même si il est caché à moitié par un sprite hard */
						if (!rastamix[i].clipped[j*2] || !rastamix[i].clipped[j*2+1]) {
							/* backup pixel */
							or=scanfloyd[j*3+0];
							ov=scanfloyd[j*3+1];
							ob=scanfloyd[j*3+2];
							/* le pixel dont on va récupérer l'indice dans la palette est le définitif */
							c=__GetIDXFromPalette(rastamix[i].palette,or,ov,ob,rastamix[i].l);
							/********************
								Amstrad memory
							********************/
							switch (tic) {
								case 0:
									zepix=0;
									if (c&1) zepix+=128;if (c&2) zepix+=8;if (c&4) zepix+=32;if (c&8) zepix+=2;
									tic=1;
									break;
								case 1:
									if (c&1) zepix+=64;if (c&2) zepix+=4;if (c&4) zepix+=16;if (c&8) zepix+=1;
									cpc[adr++]=(unsigned char)(zepix);
									tic=0;
									break;
							}

							/* comme le pixel est définitif, on le met dans la preview sans mettre à jour scanfloyd où il ne sera jamais relu */
							preview[j*6+0+i*384*3]=preview[j*6+3+i*384*3]=rastamix[i].palette[c*3+0];
							preview[j*6+1+i*384*3]=preview[j*6+4+i*384*3]=rastamix[i].palette[c*3+1];
							preview[j*6+2+i*384*3]=preview[j*6+5+i*384*3]=rastamix[i].palette[c*3+2];

							qr=(or-rastamix[i].palette[c*3+0])*floydcoef;
							qv=(ov-rastamix[i].palette[c*3+1])*floydcoef;
							qb=(ob-rastamix[i].palette[c*3+2])*floydcoef;
							/* pixel suivant prend 7/16 de l'erreur */
							if (j<191) {
								scanfloyd[j*3+0+3]+=qr*7/16;
								scanfloyd[j*3+1+3]+=qv*7/16;
								scanfloyd[j*3+2+3]+=qb*7/16;
							}
							if (i<269) {
								/* pixel du dessous en retrait prend 3/16 de l'erreur */
								if (j) {
									scanfloyd[j*3+0-3+192*3]+=qr*3/16;
									scanfloyd[j*3+1-3+192*3]+=qv*3/16;
									scanfloyd[j*3+2-3+192*3]+=qb*3/16;
								}
								/* pixel immédiatement en dessous 5/16 de l'erreur */
								scanfloyd[j*3+0+192*3]+=qr*5/16;
								scanfloyd[j*3+1+192*3]+=qv*5/16;
								scanfloyd[j*3+2+192*3]+=qb*5/16;
								/* pixel dessous à droite 1/16 de l'erreur */
								if (j<191) {
									scanfloyd[j*3+0+3+192*3]+=qr*1/16;
									scanfloyd[j*3+1+3+192*3]+=qv*1/16;
									scanfloyd[j*3+2+3+192*3]+=qb*1/16;
								}
							}
						} else {
							/* pixel is hidden by a hardware sprite, do not spread useless compensation! */
							switch (tic) {
								case 0:
									zepix=0;
									tic=1;
									break;
								case 1:
									cpc[adr++]=(unsigned char)(zepix);
									tic=0;
									break;
							}
						}
						/*
							 y a t'il un ou deux pixels de sprite hard à traiter? 
						*/
						if (rastamix[i].clipped[j*2] || rastamix[i].clipped[j*2+1]) {
							float nqr=0,nqv=0,nqb=0;
							int ihsp;
							l=0;

							/* on va récupérer la compensation moyenne à partir du pixel mode 0 */
							qr=(scanfloyd[j*3+0]-(photo->data[j*6+0+i*384*3]+photo->data[j*6+3+i*384*3])*0.5)*0.5;
							qv=(scanfloyd[j*3+1]-(photo->data[j*6+1+i*384*3]+photo->data[j*6+4+i*384*3])*0.5)*0.5;
							qb=(scanfloyd[j*3+2]-(photo->data[j*6+2+i*384*3]+photo->data[j*6+5+i*384*3])*0.5)*0.5;

							/* à gauche */
							ihsp=rastamix[i].clipped[j*2];
							if (ihsp) {
								ihsp--;
								x=j*2-hsp[ihsp].x; // coord X dans le sprite
								y=i-hsp[ihsp].y;   // coord Y dans le sprite
								l=(y*16+x)*3; // le masque et les datas sont calés
								if (ihsp<0 || ihsp>=nbhsp || l<0 || l>766) printf("ihsp=%d hx=%d hy=%d -> hsp.x=%d hsp.y=%d\n",ihsp,hsp[ihsp].x,hsp[ihsp].y,x,y);

								c=__GetIDXFromPalette(hsp[ihsp].palette,photo->data[(j*2+i*384)*3+0]+qr, photo->data[(j*2+i*384)*3+1]+qv, photo->data[(j*2+i*384)*3+2]+qb,15);
								/* update preview cause we will need it for compensation of adjacent HSP */
								preview[(j*2+i*384)*3+0]=hsp[ihsp].data[l++]=hsp[ihsp].palette[c*3+0];
								preview[(j*2+i*384)*3+1]=hsp[ihsp].data[l++]=hsp[ihsp].palette[c*3+1];
								preview[(j*2+i*384)*3+2]=hsp[ihsp].data[l]  =hsp[ihsp].palette[c*3+2];

								nqr=photo->data[(j*2+i*384)*3+0]+qr-hsp[ihsp].palette[c*3+0];
								nqv=photo->data[(j*2+i*384)*3+1]+qv-hsp[ihsp].palette[c*3+1];
								nqb=photo->data[(j*2+i*384)*3+2]+qb-hsp[ihsp].palette[c*3+2];
							}
							/* à droite */
							ihsp=rastamix[i].clipped[j*2+1];
							if (ihsp) {
								ihsp--;
								x=j*2+1-hsp[ihsp].x; // coord X dans le sprite
								y=i-hsp[ihsp].y;   // coord Y dans le sprite
								l=(y*16+x)*3; // le masque et les datas sont calés
								if (ihsp<0 || ihsp>=nbhsp || l<0 || l>766) printf("ihsp=%d hx=%d hy=%d -> hsp.x=%d hsp.y=%d\n",ihsp,hsp[ihsp].x,hsp[ihsp].y,x,y);
								c=__GetIDXFromPalette(hsp[ihsp].palette,photo->data[(j*2+1+i*384)*3+0]+qr+nqr*0.5, photo->data[(j*2+1+i*384)*3+1]+qv+nqv*0.5, photo->data[(j*2+1+i*384)*3+2]+qb+nqb*0.5,15);
								/* update preview cause we will need it for compensation of adjacent HSP */
								preview[(j*2+1+i*384)*3+0]=hsp[ihsp].data[l++]=hsp[ihsp].palette[c*3+0];
								preview[(j*2+1+i*384)*3+1]=hsp[ihsp].data[l++]=hsp[ihsp].palette[c*3+1];
								preview[(j*2+1+i*384)*3+2]=hsp[ihsp].data[l]  =hsp[ihsp].palette[c*3+2];

								nqr+=photo->data[(j*2+1+i*384)*3+0]+qr-hsp[ihsp].palette[c*3+0];
								nqv+=photo->data[(j*2+1+i*384)*3+1]+qv-hsp[ihsp].palette[c*3+1];
								nqb+=photo->data[(j*2+1+i*384)*3+2]+qb-hsp[ihsp].palette[c*3+2];
							}
							/* les pixels sont plus petits, la compensation l'est aussi! */
							qr=nqr*floydcoef*0.5;
							qv=nqv*floydcoef*0.5;
							qb=nqb*floydcoef*0.5;
							/* pixel suivant prend 7/16 de l'erreur */
							if (j<191) {
								scanfloyd[j*3+0+3]+=qr*7/16;
								scanfloyd[j*3+1+3]+=qv*7/16;
								scanfloyd[j*3+2+3]+=qb*7/16;
							}
							if (i<269) {
								/* pixel du dessous en retrait prend 3/16 de l'erreur */
								if (j) {
									scanfloyd[j*3+0-3+192*3]+=qr*3/16;
									scanfloyd[j*3+1-3+192*3]+=qv*3/16;
									scanfloyd[j*3+2-3+192*3]+=qb*3/16;
								}
								/* pixel immédiatement en dessous 5/16 de l'erreur */
								scanfloyd[j*3+0+192*3]+=qr*5/16;
								scanfloyd[j*3+1+192*3]+=qv*5/16;
								scanfloyd[j*3+2+192*3]+=qb*5/16;
								/* pixel dessous à droite 1/16 de l'erreur */
								if (j<191) {
									scanfloyd[j*3+0+3+192*3]+=qr*1/16;
									scanfloyd[j*3+1+3+192*3]+=qv*1/16;
									scanfloyd[j*3+2+3+192*3]+=qb*1/16;
								}
							}
						}

					}

					/********************
						Amstrad memory
					********************/
					adr+=2048-96;
					if (numligne<168) {
						/* bank 0 */
						if (adr>=16384) adr+=96-16384;
					} else {
						/* bank 1 */
						if (adr>=32768) adr+=96-16384;
					}
					numligne++;
					if (numligne==168) adr=16384;

					/* prêt pour la ligne suivante! */
					memcpy(&scanfloyd[0],&scanfloyd[192*3],sizeof(scanfloyd)/2);
					/* injection de nouvelles données sauf sur la dernière ligne! */
					if (i<photo->height-2)
					for (j=0;j<192;j++) {
						scanfloyd[j*3+0+1*192*3]=(photo->data[j*6+0+(i+2)*384*3]+photo->data[j*6+3+(i+2)*384*3])*0.5;
						scanfloyd[j*3+1+1*192*3]=(photo->data[j*6+1+(i+2)*384*3]+photo->data[j*6+4+(i+2)*384*3])*0.5;
						scanfloyd[j*3+2+1*192*3]=(photo->data[j*6+2+(i+2)*384*3]+photo->data[j*6+5+(i+2)*384*3])*0.5;
					}
				}





				redraw=1;
			}
		}
		/************************************************************* display **************************************/
		if (redraw) {
			unsigned int pptr;

#define GET_PHOTOPIXEL(ptr) (unsigned int)preview[(ptr)*3+2]+(unsigned int)(preview[(ptr)*3+1]<<8)+(unsigned int)(preview[(ptr)*3+0]<<16)+(0xFF<<24);

#define PUT_PIXEL(x,y,ptr) membitmap[x+(y)*winx]=(unsigned int)(*((unsigned char *)ptr+2))+(unsigned int)(*((unsigned char *)ptr+1)<<8)+(unsigned int)(*((unsigned char *)ptr+0)<<16)+(0xFF<<24);

#define PUT_LINE(x,y,vx,vy,ptr) { int lineidx,linecpt;float linevx,linevy,d;d=sqrt((vx)*(vx)+(vy)*(vy));linevx=(vx)/d;linevy=(vy)/d;linecpt=d;if (linecpt<1 || d<1.0) {} else for (lineidx=0;lineidx<linecpt;lineidx++) PUT_PIXEL((int)(x+lineidx*linevx),(int)(y+lineidx*linevy),ptr); }


			SDL_LockSurface(surface);
			membitmap=surface->pixels;
		
			if (!locked) {
				/*******************************************************
						   affichage de l'image en preview
				*******************************************************/
				for (pptr=y=0;y<photo->height;y++) {
					for (x=0;x<384;x++) {
						membitmap[x*2+y*2*winx]=GET_PHOTOPIXEL(pptr);
						membitmap[x*2+(y*2+1)*winx]=GET_PHOTOPIXEL(pptr);
						membitmap[1+x*2+y*2*winx]=GET_PHOTOPIXEL(pptr);
						membitmap[1+x*2+(y*2+1)*winx]=GET_PHOTOPIXEL(pptr);
						pptr++;
					}
				}
				if (toggle_greentea) {
					for (i=0;i<nbhsp;i++) {
						unsigned int hspcol;
						switch (hsp[i].group & 1) {
							case 0:hspcol=mygreen;break;
							default:hspcol=mywhite;break;
						}
						PUT_LINE(hsp[i].x*2,hsp[i].y*2,31,0,&hspcol);
						PUT_LINE(hsp[i].x*2,hsp[i].y*2,0,31,&hspcol);
						PUT_LINE(hsp[i].x*2,hsp[i].y*2+31,31,0,&hspcol);
						PUT_LINE(hsp[i].x*2+31,hsp[i].y*2,0,31,&hspcol);
					}
				}
				/* pour les images plus petites, on efface le bas de l'écran (surtout quand on revient du LOCKED mode */
				for (y=photo->height*2;y<winy;y++) {
					PUT_LINE(0,y,767,0,&myblack);
				}
			}

			if (legacy_display==1) {
				/************************************************************************
							affichage du HUD classique avec sprite zoomé
				************************************************************************/
				/* sprite courant affiché en mode ZOOM de y=128 à y=384 */
				if (nbhsp) {
					if (curhsp<0) curhsp=0;
					l=0;
					for (y=0;y<16;y++) {
						for (x=0;x<16;x++) {
							if (hsp[curhsp].mask[x+y*16]) {
								for (sy=0;sy<15;sy++) {
									for (sx=0;sx<15;sx++) {
										PUT_PIXEL(768+128+x*16+sx,128+y*16+sy,&hsp[curhsp].data[l+0]);
									}
									PUT_PIXEL(768+128+x*16+sx,128+y*16+sy,&myblack);
								} 
							} else {
								for (sy=0;sy<15;sy++) {
									for (sx=0;sx<15;sx++) {
										PUT_PIXEL(768+128+x*16+sx,128+y*16+sy,&myviolet);
									}
									PUT_PIXEL(768+128+x*16+sx,128+y*16+sy,&myblack);
								}
							}
							for (sx=0;sx<16;sx++) PUT_PIXEL(768+128+x*16+sx,128+y*16+sy,&myblack);
							l+=3;
						}
					}
					for (y=128;y<384;y++) {
						PUT_LINE(768,y,127,0,&myblack);
						PUT_LINE(768+128+256,y,127,0,&myblack);
					}
	#define POS_HISTO 390
					for (y=384;y<POS_HISTO;y++) PUT_LINE(768,y,511,0,&myblack);
				}
				/* sprites recopiés en bande sous le sprite zoomé à partir de y=512 */
				for (i=0;i<nbhsp;i++) {
					l=0;
					for (y=0;y<16;y++) {
						for (x=i*16;x<i*16+16;x++) {
							if (hsp[i].mask[l/3]) {
								PUT_PIXEL((384+x)*2,(254+y)*2,&hsp[i].data[l+0]);
								PUT_PIXEL((384+x)*2,(254+y)*2+1,&hsp[i].data[l+0]);
								PUT_PIXEL((384+x)*2+1,(254+y)*2,&hsp[i].data[l+0]);
								PUT_PIXEL((384+x)*2+1,(254+y)*2+1,&hsp[i].data[l+0]);
							} else {
								PUT_PIXEL((384+x)*2,(254+y)*2,&myviolet);
								PUT_PIXEL((384+x)*2,(254+y)*2+1,&myviolet);
								PUT_PIXEL((384+x)*2+1,(254+y)*2,&myviolet);
								PUT_PIXEL((384+x)*2+1,(254+y)*2+1,&myviolet);
							}
							l+=3;						
						}
					}
				}
				/* cleanup si moins de 16 sprites */
				if (nbhsp<16) {
					for (y=508;y<508+32;y++) PUT_LINE(768+nbhsp*32,y,511-nbhsp*32,0,&myblack);
				}
				/* cleanup du bas quand on revient du mode LOCKED */
				for (y=508+32;y<273*2+1;y++) PUT_LINE(768,y,511,0,&myblack);

				/*************************************************
							  h i s t o g r a m m e
				*************************************************/
	#define MERGE_PIXEL(x,y,ptr) membitmap[x+(y)*winx]|=(unsigned int)(*((unsigned char *)ptr+2))+(unsigned int)(*((unsigned char *)ptr+1)<<8)+(unsigned int)(*((unsigned char *)ptr+0)<<16)+(0xFF<<24);
				{
					unsigned int *histo[3];
					float zemax,zecoef;
					int hr,hg,hb;

					histo[0]=ImageCalcHistoR(photo->data,384,photo->height);
					histo[1]=ImageCalcHistoG(photo->data,384,photo->height);
					histo[2]=ImageCalcHistoB(photo->data,384,photo->height);

					if (histo[0][256]>histo[1][256]) zemax=histo[0][256]; else zemax=histo[1][256];
					if (zemax<histo[2][256]) zemax=histo[2][256];

					for (x=0;x<62;x++) {
						PUT_LINE(768,POS_HISTO+x,511,0,&myblack);
					}
					/* si on a 2000 pixels et qu'on veut 64 max de haut alors */
					zecoef=1.0/(zemax/64.0);

					for (x=1;x<255;x++) {
						hr=histo[0][x]*zecoef;
						hg=histo[1][x]*zecoef;
						hb=histo[2][x]*zecoef;
						for (y=0;y<hr;y++) {MERGE_PIXEL(768+x*2,POS_HISTO+64-y,&myr);MERGE_PIXEL(768+x*2+1,POS_HISTO+64-y,&myr);}
						for (y=0;y<hg;y++) {MERGE_PIXEL(768+x*2,POS_HISTO+64-y,&myg);MERGE_PIXEL(768+x*2+1,POS_HISTO+64-y,&myg);}
						for (y=0;y<hb;y++) {MERGE_PIXEL(768+x*2,POS_HISTO+64-y,&myb);MERGE_PIXEL(768+x*2+1,POS_HISTO+64-y,&myb);}
					}
					MemFree(histo[0]);
					MemFree(histo[1]);
					MemFree(histo[2]);
				}

	#define POS_COLORMAP POS_HISTO+64

	#define PUT_COLOR(r,g,b,color) {int cx,cy;cx=768+r+32*b;cy=POS_COLORMAP+g*2; PUT_PIXEL(cx+1,cy,color);PUT_PIXEL(cx+1,cy+1,color); PUT_PIXEL(cx,cy,color);PUT_PIXEL(cx,cy+1,color);}

				PUT_LINE(768,POS_COLORMAP-1,511,0,&mywhite);
				for (x=0;x<32;x++) {
					PUT_LINE(768,POS_COLORMAP+x,511,0,&myblack);
				}
				PUT_LINE(768,POS_COLORMAP+32,511,0,&mywhite);

				for (x=0;x<16+15;x++) {
					int tmpcol,tmpr,tmpg,tmpb;
					tmpr=asicolinit[x]&0xF;
					tmpg=(asicolinit[x]&0xF00)>>8;
					tmpb=(asicolinit[x]&0xF0)>>4;
					tmpcol=(tmpr<<20)+(tmpg<<12)+(tmpb<<4)+(0xFF<<24);
					PUT_COLOR(tmpr,tmpg,tmpb,&tmpcol);
				}
				for (i=1;i<photo->height;i++) {
					for (x=0;x<4;x++) {
						int tmpcol,tmpr,tmpg,tmpb;
						tmpr=rastamix[i].asicol[x]&0xF;
						tmpg=(rastamix[i].asicol[x]&0xF00)>>8;
						tmpb=(rastamix[i].asicol[x]&0xF0)>>4;
						tmpcol=(tmpr<<20)+(tmpg<<12)+(tmpb<<4)+(0xFF<<24);
						PUT_COLOR(tmpr,tmpg,tmpb,&tmpcol);
					}
					if (rastamix[j].hspad) {
						int tmpcol,tmpr,tmpg,tmpb;
						tmpr=rastamix[i].hspcol1&0xF;
						tmpg=(rastamix[i].hspcol1&0xF00)>>8;
						tmpb=(rastamix[i].hspcol1&0xF0)>>4;
						tmpcol=(tmpr<<20)+(tmpg<<12)+(tmpb<<4)+(0xFF<<24);
						PUT_COLOR(tmpr,tmpg,tmpb,&tmpcol);
						tmpr=rastamix[i].hspcol2&0xF;
						tmpg=(rastamix[i].hspcol2&0xF00)>>8;
						tmpb=(rastamix[i].hspcol2&0xF0)>>4;
						tmpcol=(tmpr<<20)+(tmpg<<12)+(tmpb<<4)+(0xFF<<24);
						PUT_COLOR(tmpr,tmpg,tmpb,&tmpcol);
					}
				}

				/* raz screen */
				for (y=POS_COLORMAP+33;y<254*2;y++) PUT_LINE(768,y,511,0,&myblack);

				if (nbhsp) {
					x=384+curhsp*16;
					y=254;
					PUT_LINE(x*2,y*2,31,0,&mygreen);
					PUT_LINE(x*2,y*2,0,31,&mygreen);
					PUT_LINE(x*2,y*2+31,31,0,&mygreen);
					PUT_LINE(x*2+31,y*2,0,31,&mygreen);
				}

				/* floydcoef */
				j=floydcoef*512;if (j>510) j=510;
				for (i=0;i<31;i++) {
					PUT_LINE(768  ,i,j,0,&mygrey);
					PUT_LINE(768+j,i,511-j,0,&myblack);
				}
				PUT_LINE(768,31,511,0,&mywhite);

				/* sharpnesscoef */
				j=sharpnesscoef*512;if (j>510) j=510;
				for (i=32;i<63;i++) {
					if (sharpnesscoef<0.1) {PUT_LINE(768  ,i,j,0,&myblack);} else PUT_LINE(768  ,i,j,0,&mygrey);
					PUT_LINE(768+j,i,511-j,0,&myblack);
				}
				PUT_LINE(768,63,511,0,&mywhite);

				/* contrastcoef */
				j=contrastcoef*512;if (j>510) j=510;
				for (i=64;i<95;i++) {
					if (contrastcoef<0.1) {PUT_LINE(768  ,i,j,0,&myblack);} else PUT_LINE(768  ,i,j,0,&mygrey);
					PUT_LINE(768+j,i,511-j,0,&myblack);
				}
				PUT_LINE(768,95,511,0,&mywhite);

				/* contrastcoef */
				if (levelup>252) levelup=255;
				if (leveldown<0) leveldown=0;
				if (levelup<leveldown) {levelup=240;leveldown=15;/* ne doit jamais arriver */}

				for (i=96;i<126;i++) {
					PUT_LINE(768,i,511,0,&mygrey);
					if (leveldown>3) PUT_LINE(768,i,leveldown*2,0,&myblack);
					if (levelup<252) PUT_LINE(768+511,i,-512+levelup*2,0,&myblack);
				}
				PUT_LINE(768,126,511,0,&mywhite);
			} else if (hspset_display) {
				/* zoom mode */
				if (wasmoving) {
					/* zoom from 768 to +511 */
					unsigned int zecol;
					int scx,scy;

					scx=hsp[wasmoving-1].x+8-32;
					scy=hsp[wasmoving-1].y+8-32;

					if (scx<0) scx=0; else if (scx>384-64) scx=384-64;
					if (scy<0) scy=0; else if (scy>photo->height-64) scy=photo->height-64;
					for (j=0;j<64;j++) {
						for (i=0;i<64;i++) {
							zecol=GET_PHOTOPIXEL((scx+i+(scy+j)*384));
							for (y=0;y<7;y++) {
								for (x=0;x<7;x++) {
									membitmap[768+(i*8+x)+(j*8+y)*winx]=zecol;
								}
								membitmap[768+(i*8+x)+(j*8+y)*winx]=0;
							}
							for (x=0;x<8;x++) membitmap[768+(i*8+x)+(j*8+y)*winx]=0;
						}
					}
					/* on affiche aussi les cadres des HSP en zoom */
					for (i=0;i<nbhsp;i++) {
						unsigned int hspcol;
						int ccx,ccy,ecx,ecy;
						switch (hsp[i].group & 1) {
							case 0:hspcol=mygreen;break;
							default:hspcol=mywhite;break;
						}
						if (hsp[i].x<0 || hsp[i].x>384-16 || hsp[i].y<0 || hsp[i].y>photo->height-16) {
							printf("hsp[%d] x=%d y=%d\n",i,hsp[i].x,hsp[i].y);
						}
						
						ccx=hsp[i].x-scx;
						ccy=hsp[i].y-scy;
						ecx=ccx+16;
						ecy=ccy+16;
						if (ccx>=64 || ecx<=0 || ccy>=64 || ecy<=0) {
							/* rien */
						} else {
							if (ccx<0) ccx=0; else if (ecx>64) ecx=64;
							if (ccy<0) ccy=0; else if (ecy>64) ecy=64;

							/* horiz */
							if (ccy!=0 || ecy-ccy==16) PUT_LINE(768+ccx*8,ccy*8,(ecx-ccx)*8-1,0,&hspcol);
							if (ecy!=64) PUT_LINE(768+ccx*8,ecy*8-1,(ecx-ccx)*8-1,0,&hspcol);
							/* vert */
							if (ccx!=0 || ecx-ccx==16) PUT_LINE(768+ccx*8,ccy*8,0,(ecy-ccy)*8-1,&hspcol);
							if (ecx!=64) PUT_LINE(768+ecx*8,ccy*8,0,(ecy-ccy)*8-1,&hspcol);
						}
					}
				}
			}
			
			if (locked) {
					/* affichage plein zoom from 0 to +767 */
					unsigned char *ptrcol;
					unsigned int zecol;
					unsigned int recol;
					int scx,scy,maxy;
					int ccx,ccy,ecx,ecy;
					int modx=2;
					if (photo->height>68) maxy=68; else maxy=photo->height;

					/* le keycursor peut changer avec la souris aussi 
						nos coord de départ scx/scy sont toujours
						sur un pixel plein!
					*/
					scx=(keycursorx&0xFFE)-48; /* zoom x4 sur 768 de large */
					scy=keycursory-34; /* zoom x4 sur 272 de haut */

					if (scx<0) scx=0; else if (scx>384-96) scx=384-96;
					if (scy<0) scy=0; else if (scy>photo->height-68) {scy=photo->height-68;if (scy<0) scy=0;}
					
					for (j=0;j<maxy;j++) {
						for (i=0;i<96;i++) {
							zecol=GET_PHOTOPIXEL((scx+i+(scy+j)*384));
							/*
							 la structure clipped est bien pratique et nous permet rapidement de savoir si on est
							 à cheval ou non sur un HSP. Alors on peut représenter les pixels mode 0 en entier
							 */
							if (((i+1) & 1) && !rastamix[scy+j].clipped[scx+i] && !rastamix[scy+j].clipped[scx+i+1]) recol=zecol; else recol=0;

							for (y=0;y<7;y++) {
								for (x=0;x<7;x++) {
									membitmap[(i*8+x)+(j*8+y)*winx]=zecol;
								}
								membitmap[(i*8+x)+(j*8+y)*winx]=recol;
							}
							for (x=0;x<8;x++) membitmap[(i*8+x)+(j*8+y)*winx]=0;
						}
					}
					/* efface le dessous pour être plus propre */
					maxy=maxy*8;
					for (i=maxy;i<winy;i++) PUT_LINE(0,i,767,0,&myblack);
					
					/* test de présence HSP != hsp[].clipped */
					for (i=0;i<nbhsp;i++) {
						if (keycursory>=hsp[i].y && keycursory<hsp[i].y+16 && (keycursorx&0xFFE)>=(hsp[i].x&0xFFE)
							&& (((keycursorx&1) && keycursorx<hsp[i].x+17) || keycursorx<hsp[i].x+16)) {
							modx=1;
							break;
						}
					}
					switch (modx) {
						case 1:
							ccx=keycursorx-scx;
							ccy=keycursory-scy;
							break;
						default:
						case 2:
							ccx=(keycursorx&0xFFE)-scx;
							ccy=keycursory-scy;
							break;
					}
					/* pixel courant encadré en vert */
					PUT_LINE(ccx*8,ccy*8,modx*8-1,0,&mygreen);
					PUT_LINE(ccx*8,(ccy+1)*8-1,modx*8-1,0,&mygreen);
					PUT_LINE(ccx*8,ccy*8,0,7,&mygreen);
					PUT_LINE((ccx+modx)*8-1,ccy*8,0,7,&mygreen);
					
					/* affichage en bleuté des cadres des HSP */
					
					for (i=0;i<nbhsp;i++) {
						if (hsp[i].x<0 || hsp[i].x>384-16 || hsp[i].y<0 || hsp[i].y>photo->height-16) {
							printf("ERROR out of bounds hsp[%d] x=%d y=%d\n",i,hsp[i].x,hsp[i].y);
						}
						
						ccx=hsp[i].x-scx;
						ccy=hsp[i].y-scy;
						ecx=ccx+16;
						ecy=ccy+16;
						if (ccx>=96 || ecx<=0 || ccy>=68 || ecy<=0) {
							/* rien */
						} else {
							/* le clipping ne tient pas compte de la hauteur de la photo car les coordonnées sont évidemment toujours OK */
							if (ccx<0) ccx=0; else if (ecx>96) ecx=96;
							if (ccy<0) ccy=0; else if (ecy>68) ecy=68;

							/* horiz */
							if (ccy!=0 || ecy-ccy==16) PUT_LINE(ccx*8,ccy*8,(ecx-ccx)*8-1,0,&mycyan);
							if (ecy!=68 || ecy-ccy==16) PUT_LINE(ccx*8,ecy*8-1,(ecx-ccx)*8-1,0,&mycyan);
							/* vert */
							if (ccx!=0 || ecx-ccx==16) PUT_LINE(ccx*8,ccy*8,0,(ecy-ccy)*8-1,&mycyan);
							if (ecx!=96 || ecx-ccx==16) PUT_LINE(ecx*8,ccy*8,0,(ecy-ccy)*8-1,&mycyan);
						}
					}

					/********************************
					             H  U  D
					********************************/

					/* petite ligne noire sur le côté pour éviter les merdouilles arrondies */
					PUT_LINE(768+511,0,0,winy-1,&myblack);

					for (i=0;i<16;i++) {
						ptrcol=&rastamix[keycursory].palette[i*3];
						for (y=0;y<32;y++) {
							for (x=0;x<32;x++) {
								PUT_PIXEL(768+i*32+x,y,ptrcol);
							}
						}
					}
					PUT_LINE(768+currentpen*32,0,31,0,&mygreen);
					PUT_LINE(768+currentpen*32,0,0,31,&mygreen);
					PUT_LINE(768+currentpen*32+31,0,0,31,&mygreen);

					j=-1;
					for (i=0;i<nbhsp;i++) {
						if (keycursory>=hsp[i].y && keycursory<hsp[i].y+16) {
							j=i;
							break;
						}
					}

					if (j>=0) {
						for (y=0;y<32;y++) {
							for (x=0;x<32;x++) {
								switch (((x>>2)+(y>>2))&1) {
									case 0:PUT_PIXEL(768+i*32+x,y+32,&mywhite);break;
									case 1:PUT_PIXEL(768+i*32+x,y+32,&mygrey);break;
								}
							}
						}
						for (i=1;i<16;i++) {
							ptrcol=&hsp[j].palette[(i-1)*3];
							for (y=0;y<32;y++) {
								for (x=0;x<32;x++) {
									PUT_PIXEL(768+i*32+x,y+32,ptrcol);
								}
							}
						}
						PUT_LINE(768+currentpen*32,63,31,0,&mygreen);
						PUT_LINE(768+currentpen*32,32,0,31,&mygreen);
						PUT_LINE(768+currentpen*32+31,32,0,31,&mygreen);
					} else {
						/* pas de HSP on raz */
						for (y=32;y<64;y++) PUT_LINE(768,y,511,0,&myblack);

						/* si pas de HSP on termine le cadre de la palette primaire */
						PUT_LINE(768+currentpen*32,31,31,0,&mygreen);
					}


					/* on recommence le même cirque, mais en cherchant le sprite actif! dans l'idée c'est le premier qui match */
					curhsp=-1;
					for (i=0;i<nbhsp;i++) {
						if (keycursory>=hsp[i].y && keycursory<hsp[i].y+16 && keycursorx>=hsp[i].x && keycursorx<hsp[i].x+16) {
							curhsp=i;
							break;
						}
					}

					for (y=64;y<70;y++) PUT_LINE(768,y,511,0,&myblack);

					if (curhsp>=0) {
						int hx,hy;
						
						hx=keycursorx-hsp[curhsp].x;
						hy=keycursory-hsp[curhsp].y;

						l=0;
						for (y=0;y<16;y++) {
							for (x=0;x<16;x++) {
								if (hsp[curhsp].mask[x+y*16]) {
									for (sy=0;sy<15;sy++) {
										for (sx=0;sx<15;sx++) {
											PUT_PIXEL(768+128+x*16+sx,70+y*16+sy,&hsp[curhsp].data[l+0]);
										}
										PUT_PIXEL(768+128+x*16+sx,70+y*16+sy,&myblack);
									} 
								} else {
									for (sy=0;sy<15;sy++) {
										for (sx=0;sx<15;sx++) {
											PUT_PIXEL(768+128+x*16+sx,70+y*16+sy,&myviolet);
										}
										PUT_PIXEL(768+128+x*16+sx,70+y*16+sy,&myblack);
									}
								}
								for (sx=0;sx<16;sx++) PUT_PIXEL(768+128+x*16+sx,70+y*16+sy,&myblack);
								l+=3;
							}
						}
						/* rapport au sprite magnifié on affiche un cadre bleuté sur le pixel courant */
						PUT_LINE(768+128+hx*16,70+hy*16,15,0,&mygreen);
						PUT_LINE(768+128+hx*16,70+hy*16,0,15,&mygreen);
						PUT_LINE(768+128+hx*16,70+hy*16+15,15,0,&mygreen);
						PUT_LINE(768+128+hx*16+15,70+hy*16,0,15,&mygreen);
						
						for (y=70;y<326;y++) {
							PUT_LINE(768,y,127,0,&myblack);
							PUT_LINE(768+128+256,y,127,0,&myblack);
						}
						for (y=326;y<330;y++) PUT_LINE(768,y,511,0,&myblack);
					} else {
						/* pas sur un HSP on efface la preview du HUD */
						for (y=70;y<330;y++) PUT_LINE(768,y,511,0,&myblack);
					}

					/*********************************************************
					   preview du graph sur le bas du HUD de 330 à winy-1 
					*********************************************************/
					ccx=keycursorx-128;
					ccy=keycursory-54;
					if (ccx<0) ccx=0;
					if (ccy<0) ccy=0;
					ecx=ccx+256;
					ecy=ccy+108;
					if (ecx>384) {ecx=384;ccx=128;}
					if (ecy>photo->height) {ecy=photo->height;ccy=photo->height-108;if (ccy<0) ccy=0;}

					sy=330*winx;
					for (y=ccy;y<ecy;y++) {
						sx=768+sy;
						for (x=ccx;x<ecx;x++) {
							zecol=GET_PHOTOPIXEL((x+y*384));
							membitmap[sx]=zecol;
							membitmap[sx+1]=zecol;
							membitmap[sx+winx]=zecol;
							membitmap[sx+winx+1]=zecol;
							sx+=2;
						}
						sy=sy+2*winx;
					}
				
			}
			

			/* cosmétique 
			PUT_LINE(768,photo->height*2+1,511,0,&mywhite);
			PUT_LINE(0,photo->height*2+1,winx-1,0,&mywhite);*/

		        SDL_UnlockSurface(surface);
		        SDL_BlitSurface(surface,NULL,screen,NULL);
		        SDL_UpdateWindowSurface(win);
			{
			char windowname[128];
			if (!locked) {
				sprintf(windowname,"%s Quantization - nblines=%d floyd=%.2lf sharp=%.2lf contrast=%.2lf level=%d/%d",WINDOW_NAME,photo->height,floydcoef,sharpnesscoef,contrastcoef,levelup,leveldown);
			} else {
				sprintf(windowname,"%s BITMAP Edition - cursor %d/%d pencil=%d",WINDOW_NAME,keycursorx,keycursory,currentpen);
			}
			SDL_SetWindowTitle(win,windowname);
			}
			redraw=0;
		}
		/* interactivité */
		SDL_PumpEvents();
		ms=SDL_GetMouseState(&gmx,&gmy);
		state=SDL_GetKeyboardState(NULL);
		
		/*
			séparer les deux modules pour simplifier le contrôle
		
			Commun aux modules:
			
				ESC: quitter
				G  : générer la solution + sauvegarde
		
			Quantization:
			
				curseur -> bouger sprite hard courant
				shift+curseur -> bouger rapidement sprite hard courant
				
				souris -> le click DOIT cantonner la souris dans la zone de click
				P -> palette
				L -> lock
		
			Palette (à venir):

				curseur + pavé numérique
				U -> unlock
				L -> lock
		
			Edition:
			
				presque OK en l'état

				curseur
				(shift ou ctrl)+curseur
				
				B
				espace
				U -> unlock
		
		*/
		
		switch (current_module) {
			case E_MODULE_QUANTIZATION:
				if (down!=SDL_BUTTON_RIGHT && (ms & SDL_BUTTON(SDL_BUTTON_RIGHT))) {
					down=SDL_BUTTON_RIGHT;
					mx=gmx;
					my=gmy;
					if (mx>768) {
						mx-=768+128;
						my-=128;
						mx/=16;
						my/=16;
						if (mx>=0 && mx<16 && my>=0 && my<16) {
							if (hsp[curhsp].mask[mx+my*16])	HSP_fill(&hsp[curhsp],mx,my); else HSP_unfill(&hsp[curhsp],mx,my);
						}
					} else {
						mx=gmx>>1;
						my=gmy>>1;
						curhsp=-1;
						for (i=0;i<nbhsp;i++) {
							if (hsp[i].x<mx && hsp[i].x>mx-16 && hsp[i].y<my && hsp[i].y>my-16) {
								curhsp=i;
								break;
							}
						}
					}
					compute=1;
				} else if (down==SDL_BUTTON_LEFT || (ms & SDL_BUTTON(SDL_BUTTON_LEFT))) {
					down=SDL_BUTTON_LEFT;
					mx=gmx;
					my=gmy;
					/* on ne fait rien dans le HUD si on était en train de bouger un sprite */
					if ((mx>768 || touchfloyd+touchsharp+touchcontrast+touchlevel+touchmask)&& !wasmoving) {
						if (!touchfloyd && !touchsharp && !touchcontrast && !touchlevel && !touchmask) {
							if (my<32) touchfloyd=1; else
							if (my<64) touchsharp=1; else
							if (my<96) touchcontrast=1; else 
							if (my<128) touchlevel=1;
						}
						
						if (touchfloyd) {
							mx-=768;
							if (mx<0) mx=0;
							floydcoef=(float)mx/512.0;
							if (floydcoef<0) floydcoef=0; else if (floydcoef>1) floydcoef=1;
							computeimage=1;
							redraw=1;
						} else if (touchsharp) {
							mx-=768;
							if (mx<0) mx=0;
							sharpnesscoef=(float)mx/512.0;
							computeglobal=1;
						} else if (touchcontrast) {
							mx-=768;
							if (mx<0) mx=0;
							contrastcoef=(float)mx/512.0;
							computeglobal=1;
						} else if (touchlevel) {
							mx-=768;
							if (mx<0) mx=0;
							mx/=2;
							if (mx<128) leveldown=mx; else levelup=mx;
							computeglobal=1;
						} else if (my>=128 && my<384 && mx>768+127 && mx<768+384) {
							touchmask=1;
							/* mask editing */
							mx-=768+128;
							my-=128;
							mx/=16;
							my/=16;
							if (mx!=omx || my!=omy) {
								if (mx>=0 && my>=0 && mx<16 && my<16) {
									if (maskvalue==-1) {
										if (hsp[curhsp].mask[mx+my*16]) {
											hsp[curhsp].mask[mx+my*16]=0;
											maskvalue=0;
										} else {
											hsp[curhsp].mask[mx+my*16]=1;
											maskvalue=1;
										}
									} else {
										hsp[curhsp].mask[mx+my*16]=maskvalue;
									}
									omx=mx;omy=my;
									compute=1;
								}
							}
							/* on est des dingues! */
						}
					} else {
						mx=gmx>>1;
						my=gmy>>1;
						
						/* au cas où on se retrouve dans le HUD ou trop bas par mégarde... */
						if (mx>383) mx=383;
						if (my>photo->height-1) my=photo->height-1;
						
						/* set hsp */
						omx=-1;omy=-1;
						if (!wasmoving) {
							curhsp=-1;
							for (i=0;i<nbhsp;i++) {
								if (hsp[i].x<mx && hsp[i].x>mx-16 && hsp[i].y<my && hsp[i].y>my-16) {
									curhsp=i;
									break;
								}
							}
							/* nouveau sprite hard */
							if (curhsp==-1 && nbhsp<16) {
								curhsp=nbhsp;
								nbhsp++;
							}
						} else {
							curhsp=wasmoving-1;
						}
						if (curhsp==-1) {
							/* tous les sprites sont pris, on vise dans le vide... */
							curhsp=0;
						} else {
							/* on centre le sprite sur le curseur de la souris, les coordonnées sont enregistrées en équivalent mode 1  */
							hsp[curhsp].x=MinMaxInt(mx-8,0,384-16);
							hsp[curhsp].y=MinMaxInt(my-8,0,photo->height-16);
							for (l=0;l<256;l++) hsp[curhsp].mask[l]=1; /* reset du mask */
							wasmoving=1+curhsp;
							legacy_display=0;
							hspset_display=1;
							//SDL_SetRelativeMouseMode(1);
							refgmx=gmx;
							refgmy=gmy;
							cumulgmx=0;
							cumulgmy=0;
						}
						/* on a la puissance pour refaire tous les calculs et réafficher! */
						compute=1;
					}
				}
				if (down==SDL_BUTTON_RIGHT && !(ms & SDL_BUTTON(SDL_BUTTON_RIGHT))) {
					//SDL_SetRelativeMouseMode(0);
					legacy_display=1;
					hspset_display=0;
					wasmoving=touchfloyd=touchsharp=touchcontrast=touchlevel=touchmask=0;
					down=0;
					downspace=0;
					maskvalue=-1;
					omx=omy=666;
				}
				if (down==SDL_BUTTON_LEFT && !(ms & SDL_BUTTON(SDL_BUTTON_LEFT))) {
					//SDL_SetRelativeMouseMode(0);
					legacy_display=1;
					hspset_display=0;
					wasmoving=touchfloyd=touchsharp=touchcontrast=touchlevel=touchmask=0;
					down=0;
					downspace=0;
					maskvalue=-1;
					omx=omy=666;
				}

				/* forcer le zoom sur le sprite si on appuie sur espace */
				if (nokey && state[SDL_SCANCODE_SPACE]) {
					
					if (!downspace) {
						if (curhsp>=0 && curhsp<nbhsp) {
							wasmoving=1+curhsp;
							legacy_display=0;
							hspset_display=1;
							compute=1;
							downspace=1;
						}
					} else {
						legacy_display=1;
						hspset_display=0;
						wasmoving=0;
						downspace=0;
						compute=1;
					}
				}
				
				/* déplacer le sprite courant au curseur */
				if (nokey && state[SDL_SCANCODE_LEFT]) {
					if (curhsp>=0 && curhsp<nbhsp) {
						hsp[curhsp].x--;
						if (hsp[curhsp].x<0) hsp[curhsp].x=0;
						compute=1;
					}
				} else if (nokey && state[SDL_SCANCODE_RIGHT]) {
					if (curhsp>=0 && curhsp<nbhsp) {
						hsp[curhsp].x++;
						if (hsp[curhsp].x>384-16) hsp[curhsp].x=384-16;
						compute=1;
					}
				} else if (nokey && state[SDL_SCANCODE_UP]) {
					if (curhsp>=0 && curhsp<nbhsp) {
						hsp[curhsp].y--;
						if (hsp[curhsp].y<0) hsp[curhsp].y=0;
						compute=1;
					}
				} else if (nokey && state[SDL_SCANCODE_DOWN]) {
					if (curhsp>=0 && curhsp<nbhsp) {
						hsp[curhsp].y++;
						if (hsp[curhsp].y>photo->height-16) hsp[curhsp].x=photo->height-16;
						compute=1;
					}
				} else if (nokey && state[SDL_SCANCODE_P]) {
					#if 0
					current_module=E_MODULE_PALETTE;
					redraw=1;
					keycursory=photo->height/2;
					#endif
				} else if (nokey && state[SDL_SCANCODE_L]) {
					current_module=E_MODULE_EDITION;
					locked=1;
					redraw=1;
					keycursorx=192;
					keycursory=photo->height/2;
				} else if (nokey && state[SDL_SCANCODE_KP_PLUS]) {
					curhsp++;
					if (curhsp>=nbhsp) {
						curhsp=0;
					}
					redraw=1;
					omx=-1;omy=-1;
				} else if (nokey && state[SDL_SCANCODE_KP_MINUS]) {
					curhsp--;
					if (curhsp<0) {
						curhsp=nbhsp-1;
					}
					redraw=1;
					omx=-1;omy=-1;
				} else if (nokey && state[SDL_SCANCODE_T]) {
					toggle_greentea=1-toggle_greentea;
					redraw=1;
				}
				
				break;
				
			case E_MODULE_PALETTE:
				if (nokey && state[SDL_SCANCODE_L]) {
					locked=1;
					redraw=1;
					keycursorx=192;
					keycursory=photo->height/2;
				}
				/* 
					affichage de la preview comme module quantization 
					
					affichage de la palette en vertical + codes RGB
					seuls les HSPAD sont éditables
					3 réglettes par accès clavier ET souris
				*/
				if (nokey && state[SDL_SCANCODE_UP]) {
					if (keycursory>2) keycursory--;
					redraw=1;
				} else if (nokey && state[SDL_SCANCODE_DOWN]) {
					if (keycursory<photo->height-1) keycursory++;
					redraw=1;
				}
				
				break;
				
			case E_MODULE_EDITION:
				if (nokey && state[SDL_SCANCODE_KP_0]) {
					currentpen--;
					if (currentpen<0) currentpen=15;
					redraw=1;
				} else if (nokey && state[SDL_SCANCODE_KP_PERIOD]) {
					currentpen++;
					if (currentpen>15) currentpen=0;
					redraw=1;
				} else if (nokey && state[SDL_SCANCODE_P]) {
					#if 0
					current_module=E_MODULE_PALETTE;
					redraw=1;
					keycursory=photo->height/2;
					#endif
				} else if (nokey && state[SDL_SCANCODE_U]) {
					current_module=E_MODULE_QUANTIZATION;
					locked=0;
					redraw=1;
				}

				if (nokey && locked && (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_B])) {
					/********************************************************************************

						le gros de l'éditeur, la mise à jour des données en preview + pseudo-RAM

					********************************************************************************/
						int ishsp,curadr,doin;
						int hx,hy,repoke=1;
						int xmode0;

						/* on est obligé de scanner pour pouvoir éventuellement activer un pixel inactif de HSP */
						for (ishsp=0;ishsp<nbhsp;ishsp++) {
							if (keycursory>=hsp[ishsp].y && keycursory<hsp[ishsp].y+16 && keycursorx>=hsp[ishsp].x && keycursorx<hsp[ishsp].x+16) break;
						}

						/* dans le cas où on est en plein un HSP avec des pixels transparents, la touche B permet de savoir
						   qu'on veut établir la couleur du background et pas réactiver des pixels du sprite avec le pinceau
						*/
						if (ishsp<nbhsp && state[SDL_SCANCODE_B]) {
							rastamix[keycursory].clipped[keycursorx]=0;
							hx=keycursorx-hsp[ishsp].x;
							hy=keycursory-hsp[ishsp].y;
							hsp[ishsp].mask[hx+hy*16]=0;
							/* le pixel ne doit plus être celui du sprite! On annule l'édition du sprite avec un index pourri */
							ishsp=666;
						}

						if (ishsp<nbhsp) {
							/* poke */
							repoke=0;
							hx=keycursorx-hsp[ishsp].x;
							hy=keycursory-hsp[ishsp].y;
							if (currentpen) {
								int ipen;
								/* mettre à jour le clipped pour l'affichage */
								rastamix[keycursory].clipped[keycursorx]=ishsp+1;
								hsp[ishsp].mask[hx+hy*16]=1;
								ipen=currentpen-1;
								preview[(keycursorx+keycursory*384)*3+0]=hsp[ishsp].palette[ipen*3+0];
								preview[(keycursorx+keycursory*384)*3+1]=hsp[ishsp].palette[ipen*3+1];
								preview[(keycursorx+keycursory*384)*3+2]=hsp[ishsp].palette[ipen*3+2];
								hsp[ishsp].data[(hx+hy*16)*3+0]=hsp[ishsp].palette[ipen*3+0];
								hsp[ishsp].data[(hx+hy*16)*3+1]=hsp[ishsp].palette[ipen*3+1];
								hsp[ishsp].data[(hx+hy*16)*3+2]=hsp[ishsp].palette[ipen*3+2];
							} else {
								rastamix[keycursory].clipped[keycursorx]=0;
								hsp[ishsp].mask[hx+hy*16]=0;
								repoke=1;
								/* il faut gérer les chevauchements de HSP */
								while (ishsp<nbhsp+1) {
									ishsp++;
									if (keycursory>=hsp[ishsp].y && keycursory<hsp[ishsp].y+16 && keycursorx>=hsp[ishsp].x && keycursorx<hsp[ishsp].x+16) {
										hx=keycursorx-hsp[ishsp].x;
										hy=keycursory-hsp[ishsp].y;
										hsp[ishsp].mask[hx+hy*16]=0;
									} else if (hsp[ishsp].y>keycursory) break;
								}
							}
						}
						/* on poke le pixel si on est dessus OU si on passe le sprite en transparence */
						if (repoke) {
							int wpix;
							/*********************
								Amstrad memory
							*********************/
							curadr=rastamix[keycursory].adr+(keycursorx>>2);
							zepix=cpc[curadr];
							c=currentpen;
							doin=1;
							/* en fonction du pixel dans l'octet */
							switch ((keycursorx>>1)&1) {
								case 0:
									/* on garde les bits de l'autre pixel */
									zepix&=64+16+4+1;
									if (c&1) zepix+=128;if (c&2) zepix+=8;if (c&4) zepix+=32;if (c&8) zepix+=2;
									cpc[curadr]=(unsigned char)zepix;
									if (keycursorx&1) wpix=-1; else wpix=1;
									if (!rastamix[keycursory].clipped[keycursorx+wpix]) doin=2;
									break;
								case 1:
									/* on garde les bits de l'autre pixel */
									zepix&=128+32+8+2;
									if (c&1) zepix+=64;if (c&2) zepix+=4;if (c&4) zepix+=16;if (c&8) zepix+=1;
									cpc[curadr]=(unsigned char)zepix;
									if (keycursorx&1) wpix=-1; else wpix=1;
									if (!rastamix[keycursory].clipped[keycursorx+wpix]) doin=2;
									break;
							}

							/* mise à jour de la preview */
							preview[(keycursorx+keycursory*384)*3+0]=rastamix[keycursory].palette[currentpen*3+0];
							preview[(keycursorx+keycursory*384)*3+1]=rastamix[keycursory].palette[currentpen*3+1];
							preview[(keycursorx+keycursory*384)*3+2]=rastamix[keycursory].palette[currentpen*3+2];
							if (doin==2) {
								if (keycursorx&1) doin=-3; else doin=3;
								preview[(keycursorx+keycursory*384)*3+0+doin]=rastamix[keycursory].palette[currentpen*3+0];
								preview[(keycursorx+keycursory*384)*3+1+doin]=rastamix[keycursory].palette[currentpen*3+1];
								preview[(keycursorx+keycursory*384)*3+2+doin]=rastamix[keycursory].palette[currentpen*3+2];
							}
						}

					redraw=1;
					/* done */
				}
				
				/* left/right et up/down distincts de B ou espace */
				if (nokey && locked && state[SDL_SCANCODE_LEFT]) {
					int modx=2;
					for (i=0;i<nbhsp;i++) {
						if (keycursory>=hsp[i].y && keycursory<hsp[i].y+16 && (keycursorx&0xFFE)>=(hsp[i].x&0xFFE)
							&& (((keycursorx&1) && keycursorx<hsp[i].x+17) || keycursorx<hsp[i].x+16)) {
							modx=1;
							break;
						}
					}
					switch (modx) {
						case 1:
						keycursorx-=modx;
						if (keycursorx<0) keycursorx=0;
						break;
						default:
						case 2:
						keycursorx-=modx;
						if (keycursorx<0) keycursorx=0;
						keycursorx=(keycursorx&0xFFE)+1;
						break;
					}
					redraw=1;
				} else if (nokey && locked && state[SDL_SCANCODE_RIGHT]) {
					int modx=2;
					for (i=0;i<nbhsp;i++) {
						if (keycursory>=hsp[i].y && keycursory<hsp[i].y+16 && (keycursorx&0xFFE)>=(hsp[i].x&0xFFE)
							&& (((keycursorx&1) && keycursorx<hsp[i].x+17) || keycursorx<hsp[i].x+16)) {
							modx=1;
							break;
						}
					}
					switch (modx) {
						case 1:
						keycursorx+=modx;
						if (keycursorx>383) keycursorx=383;
						break;
						default:
						case 2:
						keycursorx&=0xFFE;
						keycursorx+=modx;
						if (keycursorx>383) keycursorx=382;
						break;
					}
					redraw=1;
				}
				/* up/down distincts de left/right */
				if (nokey && locked && state[SDL_SCANCODE_UP]) {
					if (keycursory>0) keycursory--;
					redraw=1;
				} else if (nokey && locked && state[SDL_SCANCODE_DOWN]) {
					if (keycursory<photo->height-1) keycursory++;			
					redraw=1;
				}

				break;
		}


		/********************************************************************************
		     t o u c h e s   c o m m u n e s   à   t o u s   l e s   m o d u l e s
		********************************************************************************/
		if (nokey && state[SDL_SCANCODE_ESCAPE]) {
			redo--;
			if (redo<0) redo=0;
		}

		if (nokey && state[SDL_SCANCODE_G]) {
			/* generate data */
			char buftmp[4096],bufint[8];

			FileRemoveIfExists(cprasmfilename);
			FileWriteLine(cprasmfilename,"; splitraster+ v7 automatic CPR generated code\n");
			FileWriteLine(cprasmfilename,"buildcpr\nbank 0\norg 0\njr afterint38\n");
			FileWriteLine(cprasmfilename,"crtc_data: defb #3f, 48, 50, #8e, 38, 0, 34, 35, #00, #07, #00,#00,#30,#00,#c0,#00\nend_crtc_data:\n");
			FileWriteLine(cprasmfilename,"asicunlockseq: defb #ff,#00,#ff,#77,#b3,#51,#a8,#d4,#62,#39,#9c,#46,#2b,#15,#8a,#cd,#ee\n");
			FileWriteLine(cprasmfilename,"org #38\n int38vector\n ei\n ret\n afterint38\n\n");
			FileWriteLine(cprasmfilename,"ld hl,0: ld de,0: ld bc,myinit: ldir\n");
			FileWriteLine(cprasmfilename,"rom_entry:ld hl,#c9fb: ld (#38),hl: im 1: ld bc,#f782: out (c),c: ld bc,#f400: out (c),c: ld bc,#f600: out (c),c: ld bc,#7fc0: out (c),c\n");
			FileWriteLine(cprasmfilename,"; mode 0 and small stack\n");
			FileWriteLine(cprasmfilename,"ld b,#7F: ld c,%10001100: out (c),c: ld sp,#38: ei\n");
			FileWriteLine(cprasmfilename,"ld b,#bc: ld hl,asicunlockseq: ld e,17: seq: ld a,(hl): out (c),a: inc hl: dec e: jr nz,seq\n");
			FileWriteLine(cprasmfilename,"ld hl,end_crtc_data: ld bc,#bc0f: crtc_loop: out (c),c: dec hl: ld a,(hl): inc b: out (c),a: dec b: dec c: jp p,crtc_loop\n");
			FileWriteLine(cprasmfilename,"ld bc,#7fb8: out (c),c\n");
			FileWriteLine(cprasmfilename,"; reset SSR / split screen line 168 / all colors to black\n");
			FileWriteLine(cprasmfilename,"xor a: ld (#6804),a: ld a,167: ld (#6801),a: ld hl,#0020: ld (#6802),hl: ld hl,#6400: ld b,66: .loop: ld (hl),0: inc l: djnz .loop\n");
			FileWriteLine(cprasmfilename,"ld a,1:ld (#6800),a\n");
			FileWriteLine(cprasmfilename,"; init sprites/zoom coordinates\n");
			FileWriteLine(cprasmfilename,"ld bc,#10FF: ld hl,HSP_coordinates: ld de,#6000: ld a,9 ; sprite zoom like mode 1\n");
			FileWriteLine(cprasmfilename,"HSPLoopInit: ldi: ldi: ldi: ldi: ld (de),a: inc e: inc e: inc e: inc e: djnz HSPLoopInit\n");
			FileWriteLine(cprasmfilename,"; hardware sprite copy\n");
			FileWriteLine(cprasmfilename,"ld a,0: ld e,1: call SelectUpperRom\n");
			FileWriteLine(cprasmfilename,"ld hl,#C000: ld de,#4000: ld bc,2048+256\n");
			FileWriteLine(cprasmfilename,"HSPCopyLoop: ld a,(hl): and #F0: rrca: rrca: rrca: rrca: ld (de),a: inc e\n");
			FileWriteLine(cprasmfilename,"ld a,(hl): inc hl: and #F: ld (de),a: inc de\n");
			FileWriteLine(cprasmfilename,"dec c: jr nz,HSPCopyLoop: djnz HSPCopyLoop\n");
			FileWriteLine(cprasmfilename,"; upper screen\n");
			FileWriteLine(cprasmfilename,"ld a,0: ld e,3: call SelectUpperRom: ld hl,#C000: ld de,#8000: ld bc,16384: ldir\n");
			FileWriteLine(cprasmfilename,"; bottom screen\n");
			FileWriteLine(cprasmfilename,"ld a,0: ld e,2: call SelectUpperRom: ld hl,#C000: ld de,#C000: ld bc,16384: ldir\n");
			FileWriteLine(cprasmfilename,"mainloopraster:\n");
			FileWriteLine(cprasmfilename,"jr RastaLoop\n");
			sprintf(buftmp,"read '%s'\n",asmfilename); FileWriteLine(cprasmfilename,buftmp);
			FileWriteLine(cprasmfilename,"EI\n");
			FileWriteLine(cprasmfilename,"JP mainloopraster\n");
			FileWriteLine(cprasmfilename,"SelectUpperRom:and %11: or %10000100: ld b,#7F: out (c),a: ld a,e: or #80: and %10011111: ld b,#DF: out (c),a: ret\n");
			FileWriteLine(cprasmfilename,"myinit\n");
			FileWriteLine(cprasmfilename,"bank 1\n");
			sprintf(buftmp,"incbin '%s'\n",sprfilename); FileWriteLine(cprasmfilename,buftmp);
			FileWriteLine(cprasmfilename,"bank 2\n");
			sprintf(buftmp,"incbin '%s'\n",scrfilename1); FileWriteLine(cprasmfilename,buftmp);
			FileWriteLine(cprasmfilename,"bank 3\n");
			sprintf(buftmp,"incbin '%s'\n",scrfilename2); FileWriteLine(cprasmfilename,buftmp);
			FileWriteLine(cprasmfilename,";EOF\n");
			FileWriteLineClose(cprasmfilename);


			FileRemoveIfExists(asmfilename);
			FileWriteLine(asmfilename,"; SPLITSDL v8.0 - code genere pour le fichier ");
			FileWriteLine(asmfilename,filename);
			FileWriteLine(asmfilename,"\n;\n;\nHSP_coordinates ; zoom=9 #6804 etc.\n");
			/* coordonnées HSP */
			for (i=0;i<nbhsp;i++) {
				sprintf(cpccode,"DEFW #%X,#%X ; x/y sprite %d\n",hsp[i].x*2,hsp[i].y,i);
				FileWriteLine(asmfilename,cpccode);
			}
			for (;i<16;i++) {
				sprintf(cpccode,"DEFW #%X,#%X ; x/y sprite %d inactif\n",768,273,i);
				FileWriteLine(asmfilename,cpccode);
			}

			FileWriteLine(asmfilename,"\n\nRastaLoop\n");
			/* couleurs d'init */
			for (j=0;j<16;j++) {
				sprintf(cpccode,"LD HL,#%04X\nLD (#%04X),HL\n",asicolinit[j],0x6400+j*2);
				FileWriteLine(asmfilename,cpccode);
			}
			/* couleurs d'init HSP */
			for (j=0;j<15;j++) {
				sprintf(cpccode,"LD HL,#%04X\nLD (#%04X),HL\n",asicolinit[j+16],0x6422+j*2);
				FileWriteLine(asmfilename,cpccode);
			}
			
			FileWriteLine(asmfilename,"HALT\nDI\nDEFS 5,0\nLD B,3\nDJNZ $\n");

			/**** rastamix start ****/
			artefacts=artebis=0;
			for (j=2;j<photo->height;j++) {
				int tmpswitchcol,tmpswitchad,dekal;
				/* existe-t'il un raster dont aucune couleur ne fait partie des 4 derniers pixels? -> probabilité de réussite forte */
				memset(clipcol,0,sizeof(clipcol));
				for (i=188;i<192;i++) {
					clipcol[__GetIDXFromPalette(rastamix[j-1].palette,preview[i*6+0+(j-1)*384*3],preview[i*6+1+(j-1)*384*3],preview[i*6+2+(j-1)*384*3],rastamix[j-1].l)]=1;
				}
				if (!clipcol[(rastamix[j].asicad[0]-0x6400)/2]) {
					/* tout est ok on commencera par modifier la couleur 0 */
					i=0;
				} else {
					for (i=1;i<4;i++) if (!clipcol[(rastamix[j].asicad[i]-0x6400)/2]) {
						/* une autre couleur logique 1,2 ou 3 */
						tmpswitchcol=rastamix[j].asicol[0];
						tmpswitchad=rastamix[j].asicad[0];
						rastamix[j].asicol[0]=rastamix[j].asicol[i];
						rastamix[j].asicad[0]=rastamix[j].asicad[i];
						rastamix[j].asicol[i]=tmpswitchcol;
						rastamix[j].asicad[i]=tmpswitchad;
						nopfirst=0;
						break;
					}
				}
				if (i==4) {
					artebis++;
					/************* optimisation de seconde chance ***************************
					changer le timing de deux NOPS pour retarder et regarder la ligne à venir
					existe-t'il un raster dont aucune couleur ne fait partie des 8 premiers pixels? -> appliquer et changer timing de fin */
					if (j+1>=photo->height) {
						/* c'est la dernière ligne on est bon! */
						nopfirst=2;
					} else {
						memset(clipcol,0,sizeof(clipcol));
						for (i=0;i<8;i++) {
							clipcol[__GetIDXFromPalette(rastamix[j-1].palette,preview[i*6+0+j*384*3],preview[i*6+1+j*384*3],preview[i*6+2+j*384*3],rastamix[j-1].l)]=1;
						}
						if (!clipcol[(rastamix[j].asicad[3]-0x6400)/2]) {
							/* tout est ok on terminera par modifier la couleur 3 */
							i=0;
						} else {
							for (i=0;i<3;i++) if (!clipcol[(rastamix[j].asicad[i]-0x6400)/2]) {
								/* une autre couleur logique 1,2 ou 3 */
								tmpswitchcol=rastamix[j].asicol[3];
								tmpswitchad=rastamix[j].asicad[3];
								rastamix[j].asicol[3]=rastamix[j].asicol[i];
								rastamix[j].asicad[3]=rastamix[j].asicad[i];
								rastamix[j].asicol[i]=tmpswitchcol;
								rastamix[j].asicad[i]=tmpswitchad;
								nopfirst=0;
								break;
							}
						}
						if (i==4) {
							/* on n'a pas trouvé de couleur adéquate */
							artefacts++;
						}
					}
				}
				
				if (nopfirst==2) FileWriteLine(asmfilename,"NOP 2\n");
				/* legacy raster commence 2 NOPS trop tôt à changer d'encre */
				sprintf(cpccode,"LD IX,#%04X\nLD BC,#%04X\nLD DE,#%04X\nLD HL,#%04X\nLD (#%04X),IX\nLD (#%04X),BC\nLD (#%04X),DE\nLD (#%04X),HL\n",
					rastamix[j].asicol[0],rastamix[j].asicol[1],rastamix[j].asicol[2],rastamix[j].asicol[3],
					rastamix[j].asicad[0],rastamix[j].asicad[1],rastamix[j].asicad[2],rastamix[j].asicad[3]);
				FileWriteLine(asmfilename,cpccode);
				if (nopfirst==2) FileWriteLine(asmfilename,"NOP 2\n"); else FileWriteLine(asmfilename,"NOP 4\n");
				
				/* hsp raster 24 nops both cases */
				if (rastamix[j].hspad) {
					sprintf(cpccode,"LD HL,#%04X\nLD (HL),#%02X\nINC L\nLD (HL),#%02X\nINC L\nLD (HL),#%02X\nINC L\nLD (HL),#%02X\nLD B,1\nDJNZ $\nNOP\n",rastamix[j].hspad,
						rastamix[j].hspcol1&0xFF,rastamix[j].hspcol1>>8,rastamix[j].hspcol2&0xFF,rastamix[j].hspcol2>>8);
					FileWriteLine(asmfilename,cpccode);
				} else {
					FileWriteLine(asmfilename,"LD B,4\nNOP\nDJNZ $-1\nNOP 3\n");
				}
			
			}
			if (artebis-artefacts) {
				printf("INFO   : %d artefact%s fixed\n",artebis-artefacts,artebis-artefacts>1?"s":"");
			}
			if (artefacts) {
				printf("WARNING: %d artefact%s detected\n",artefacts,artefacts>1?"s":"");
			}
			/**** rastamix end ****/
			loginfo("writing [%s] preview -> WARNING THIS PREVIEW MAY NOT BE ACCURATE, CHECK ON REAL HARDWARE!",previewfilename);
			memcpy(photo->data,preview,384*photo->height*3);
			PNGWrite(photo,previewfilename);
			memcpy(photo->data,data,384*photo->height*3);
		
	
			loginfo("writing files...");
			FileRemoveIfExists(scrfilename1);
			FileRemoveIfExists(scrfilename2);
			FileWriteBinary(scrfilename1,cpc,16384);
			FileWriteBinary(scrfilename2,cpc+16384,16384);
			FileWriteBinaryClose(scrfilename1);
			FileWriteBinaryClose(scrfilename2);

			/* comptage bourrin des couleurs */
			cptpalette=MemMalloc(4096*sizeof(int));
			memset(cptpalette,0,4096*sizeof(int));
			for (i=0;i<photo->height;i++) {
				cptpalette[rastamix[i].asicol[0]]=1;
				cptpalette[rastamix[i].asicol[1]]=1;
				cptpalette[rastamix[i].asicol[2]]=1;
				cptpalette[rastamix[i].asicol[3]]=1;
				if (rastamix[i].hspad) {
					cptpalette[rastamix[i].hspcol1]=1;
					cptpalette[rastamix[i].hspcol2]=1;
				}
			}
			for (i=j=0;i<4096;i++) {
				if (cptpalette[i]) j++;
			}
			loginfo("%d couleurs dans l'image finale pour un maximum théorique de %d",j,16+4*268+11*16);
			sprintf(cpccode,"; %d couleurs differentes\n; maximum theorique %d",j,16+4*268+11*16);
			FileWriteLine(asmfilename,cpccode);
			FileWriteLineClose(asmfilename);
			MemFree(cptpalette);				

			FileRemoveIfExists(sprfilename);
			for (i=0;i<16;i++) {
				if (i<nbhsp) {
					/* correspondance palette index */
					for (l=0;l<256;l++) {
						if (hsp[i].mask[l]) {
							cpccode[l]=1+__GetIDXFromPalette(hsp[i].palette, hsp[i].data[l*3+0], hsp[i].data[l*3+1], hsp[i].data[l*3+2],15);
						} else {
							cpccode[l]=0;
						}
					}
					for (l=0;l<128;l++) {
						cpccode[l]=cpccode[l*2]*16+cpccode[l*2+1];
					}
				} else {
					for (l=0;l<128;l++) cpccode[l]=0;
				}
				FileWriteBinary(sprfilename,cpccode,128);
			}
		
			FileWriteBinaryClose(sprfilename);
			
			/* enregistre dans un XML la position des sprites et le masque */
			FileRemoveIfExists(xmlfilename);
			sprintf(buftmp,"	<height v=\"%d\"/>\n",photo->height); FileWriteLine(xmlfilename,buftmp);
			
			sprintf(buftmp,"	<module v=\"%d\"/>\n",current_module); FileWriteLine(xmlfilename,buftmp);
			sprintf(buftmp,"	<keycursorx v=\"%d\"/>\n",keycursorx); FileWriteLine(xmlfilename,buftmp);
			sprintf(buftmp,"	<keycursory v=\"%d\"/>\n",keycursory); FileWriteLine(xmlfilename,buftmp);
			sprintf(buftmp,"	<floyd v=\"%.2lf\"/>\n",floydcoef); FileWriteLine(xmlfilename,buftmp);
			sprintf(buftmp,"	<sharp v=\"%.2lf\"/>\n",sharpnesscoef); FileWriteLine(xmlfilename,buftmp);
			sprintf(buftmp,"	<contrast v=\"%.2lf\"/>\n",contrastcoef); FileWriteLine(xmlfilename,buftmp);
			sprintf(buftmp,"	<levelup v=\"%d\"/>\n",levelup); FileWriteLine(xmlfilename,buftmp);
			sprintf(buftmp,"	<leveldown v=\"%d\"/>\n",leveldown); FileWriteLine(xmlfilename,buftmp);

			FileWriteLine(xmlfilename,"<sprites>\n");
			for (i=0;i<nbhsp;i++) {
				sprintf(buftmp,"	<sprite x=\"%d\" y=\"%d\" group=\"%d\" ",hsp[i].x,hsp[i].y,hsp[i].group);
				FileWriteLine(xmlfilename,buftmp);
				
				for (j=0;j<45;j++) {
					sprintf(buftmp,"p%02d=\"%d\" ",j,hsp[i].palette[j]);
					FileWriteLine(xmlfilename,buftmp);
				}
				FileWriteLine(xmlfilename,">\n");
				
				/* masque output */
				strcpy(buftmp,"		<mask>");
				for (l=0;l<256;l++) {
					sprintf(bufint,"%s",hsp[i].mask[l]>0?"1":"0");
					strcat(buftmp,bufint);
				}
				strcat(buftmp,"</mask>\n");
				FileWriteLine(xmlfilename,buftmp);
				/* data output */
				strcpy(buftmp,"		<data>");
				for (l=0;l<768;l++) {
					sprintf(bufint,"%02X",hsp[i].data[l]);
					strcat(buftmp,bufint);
				}
				strcat(buftmp,"</data>\n");
				FileWriteLine(xmlfilename,buftmp);
				FileWriteLine(xmlfilename,"	</sprite>\n");
			}
			FileWriteLine(xmlfilename,"</sprites>\n");
			
			if (locked) {
				FileWriteLine(xmlfilename,"<rastainit ");
					for (j=0;j<31;j++) {
						sprintf(buftmp,"asicolinit%02d=\"%d\" ",j,asicolinit[j]);
						FileWriteLine(xmlfilename,buftmp);
					}
				FileWriteLine(xmlfilename," />\n");
				/* en mode locked il faut enregistrer beaucoup plus d'infos */
				FileWriteLine(xmlfilename,"<rastamixtab>\n");
				for (i=0;i<photo->height;i++) {
					sprintf(buftmp,"	<rastamix ");
					FileWriteLine(xmlfilename,buftmp);
					
					for (j=0;j<4;j++) {
						if (i>1 && rastamix[i].asicad[j]<0x6400) {
							printf("XML writing corrupted as asicad cannot be NULL\n");
							exit(-2);
						}
						sprintf(buftmp,"asicad%02d=\"%d\" ",j,rastamix[i].asicad[j]);
						FileWriteLine(xmlfilename,buftmp);
						sprintf(buftmp,"asicol%02d=\"%d\" ",j,rastamix[i].asicol[j]);
						FileWriteLine(xmlfilename,buftmp);
					}
					sprintf(buftmp,"hspad=\"%d\" ",rastamix[i].hspad);
					FileWriteLine(xmlfilename,buftmp);
					sprintf(buftmp,"hspcol1=\"%d\" ",rastamix[i].hspcol1);
					FileWriteLine(xmlfilename,buftmp);
					sprintf(buftmp,"hspcol2=\"%d\" ",rastamix[i].hspcol2);
					FileWriteLine(xmlfilename,buftmp);
					sprintf(buftmp,"adr=\"%d\" ",rastamix[i].adr);
					FileWriteLine(xmlfilename,buftmp);
					sprintf(buftmp,"l=\"%d\" ",rastamix[i].l);
					FileWriteLine(xmlfilename,buftmp);
					for (j=0;j<48;j++) {
						sprintf(buftmp,"p%02d=\"%d\" ",j,rastamix[i].palette[j]);
						FileWriteLine(xmlfilename,buftmp);
					}
					
					sprintf(buftmp," />\n");
					FileWriteLine(xmlfilename,buftmp);
				}
				
				FileWriteLine(xmlfilename,"</rastamixtab>\n");

				FileWriteLine(xmlfilename,"<preview>");
				for (j=0;j<photo->height*3;j++) {
					buftmp[0]=0;
					for (k=0;k<384;k++) {
						sprintf(bufint,"%02X",preview[j*384+k]);
						strcat(buftmp,bufint);
					}
					FileWriteLine(xmlfilename,buftmp);
				}
				FileWriteLine(xmlfilename,"</preview>\n");
				
				FileWriteLine(xmlfilename,"<cpcdata>");
				for (j=0;j<32;j++) {
					buftmp[0]=0;
					for (k=0;k<1024;k++) {
						sprintf(bufint,"%02X",cpc[k+j*1024]);
						strcat(buftmp,bufint);
					}
					FileWriteLine(xmlfilename,buftmp);
				}
				FileWriteLine(xmlfilename,"</cpcdata>\n");
			}			
			
			
			FileWriteLineClose(xmlfilename);
			loginfo("done");
		}

		if ( state[SDL_SCANCODE_ESCAPE]+state[SDL_SCANCODE_KP_PLUS]+state[SDL_SCANCODE_KP_MINUS]+state[SDL_SCANCODE_T]+state[SDL_SCANCODE_G]
			+state[SDL_SCANCODE_L]+state[SDL_SCANCODE_U]+state[SDL_SCANCODE_P]
			+state[SDL_SCANCODE_KP_0]+state[SDL_SCANCODE_KP_PERIOD]
			+state[SDL_SCANCODE_DOWN]+state[SDL_SCANCODE_UP]+state[SDL_SCANCODE_RIGHT]+state[SDL_SCANCODE_LEFT]+state[SDL_SCANCODE_SPACE])
				nokey=0; else nokey=1;
				
		if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]) {
			/* SHIFT ou CTRL accélère tous les boutons */
			nokey=1;
			SDL_Delay(10);
		}

		if (!redraw) {
			SDL_Delay(1);
		}
	}


	PNGFree(&photo);
	MemFree(data);
	MemFree(preview);
	MemFree(rastamix);
	return 0;
}

/***************************************
	semi-generic body of program
***************************************/

/*
	Usage
	display the mandatory parameters
*/
void Usage()
{
	#undef FUNC
	#define FUNC "Usage"
	
	printf("%.*s.exe v8.0 / Edouard BERGE 2016 (build 2019-06)\n",(int)(sizeof(__FILENAME__)-3),__FILENAME__);
	printf("--- this software is designed to run with colorful images, avoid conversion from Atari/Amiga ---\n");
	printf("           introducing for the first time ASS technology (Amstrad Split Solver)\n");
	printf("\n");
	printf("USAGE: splitsdl.exe picture.png\n");
	printf("\n");	
	printf("input file must be PNG with 384 pixels width (mode 1 ratio) and from 16 to 273 pixels height\n");
	printf("if the picture does not fit required size, a crappy resize will be done, AVOID THIS!\n");
	printf("\n");
	printf("CONTROLS DURING QUANTIZATION\n");
	printf("click in the picture to add an hardware sprite\n");
	printf("click&move an hardware sprite in the picture to move it\n");
	printf("left-click and draw in the magnified sprite to enable/disable transparency\n");
	printf("right-click to fill or unfill transparency on the very same color\n");
	printf("G generate files and save settings\n");
	printf("L lock screen in order to edit pixels\n");
	printf("ESC press twice to quit\n");
	printf("\n");
	printf("CONTROLS DURING PIXEL EDITION\n");
	printf("keypad 0 or . to select current pencil (like OCP)\n");
	printf("cursor to move current pixel position\n");
	printf("shift or ctrl + cursor to move current pixel position faster\n");
	printf("space to put pixel in the background OR the hardware sprite\n");
	printf("B to put a background pixel on a hardware sprite (will enable transparency)\n");
	printf("U unlock screen and goes back to quantization mode (all modifications will be lost)\n");
	printf("G generate files and save settings\n");
	printf("ESC press twice to quit\n");
	
	exit(ABORT_ERROR);
}


/*
	ParseOptions
	
	used to parse command line and configuration file
*/
int ParseOptions(char **argv,int argc, char **zepic, int *dithering, int *uniform)
{
	#undef FUNC
	#define FUNC "ParseOptions"
	int i=0;

	if (argv[i][0]=='-')
	{
		switch(argv[i][1])
		{
			case 'I':
			case 'i':
				if (i+1<argc) {
					*zepic=argv[++i];
					break;
				}
				Usage();
			case 'H':
			case 'h':Usage();
			default:
				Usage();				
		}
	}
	else {
		if (!*zepic) *zepic=argv[i]; else
		Usage();
	}
	return i;
}

/*
	GetParametersFromCommandLine	
	retrieve parameters from command line and fill pointers to file names
*/
void GetParametersFromCommandLine(int argc, char **argv, char **zepic, int *dithering, int *uniform)
{
	#undef FUNC
	#define FUNC "GetParametersFromCommandLine"
	int i;
	
	for (i=1;i<argc;i++)
		i+=ParseOptions(&argv[i],argc-i,zepic,dithering,uniform);

	if (!*zepic) Usage();
}

/*
	main
	
	check parameters
	execute the main processing
*/
int main(int argc, char **argv)
{
	#undef FUNC
	#define FUNC "main"

	char *zepic=NULL;
	int dithering=0;
	int uniform=0;

	GetParametersFromCommandLine(argc,argv,&zepic,&dithering,&uniform);
	Build(zepic,dithering,uniform);
	//CloseLibrary();
    SDL_Quit();
	return 0;
}




