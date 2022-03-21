#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<gd.h>

int main(int argc, char *argv[]){

    int color,red,green,blue;
    int w,h,x,y;
    int tid;

    if(argc!=3){
        printf("Arguments missing\n");
        exit(0);
    }

    char *iname=argv[1];
    char *oname=argv[2];
    FILE *fp;

    if((fp=fopen(iname,"r"))==NULL){
        printf("Failed to open input file\n");
        exit(0);
    }

    gdImagePtr img=gdImageCreateFromPng(fp);
    w=gdImageSX(img);
    h=gdImageSY(img);

    double t=omp_get_wtime();
    omp_set_num_threads(4);
    #pragma omp parallel for private(y,color,red,green,blue) schedule(static,50) //schedule(dynamic,50) or schedule(guided,50)
    for(x=0;x<w;x++){
        for(y=0;y<h;y++){
            tid=omp_get_thread_num();
            color=gdImageGetPixel(img,x,y);
            red=gdImageRed(img,color);
            green=gdImageGreen(img,color);
            blue=gdImageBlue(img,color);

            if(tid==0){
                color=gdImageColorAllocate(img,red,0,0);
            }
            else if(tid==1){
                color=gdImageColorAllocate(img,0,green,0);
            }
            else if(tid==2){
                color=gdImageColorAllocate(img,0,0,blue);
            }
            else if(tid==3){
                color=gdImageColorAllocate(img,0,0,0);
            }
            
            gdImageSetPixel(img,x,y,color);
        }
    }

    t=omp_get_wtime()-t;

    if((fp=fopen(oname,"w"))==NULL){
        printf("Failed to open output file\n");
        exit(0);
    }

    gdImagePng(img,fp);
    fclose(fp);
    gdImageDestroy(img);

    printf("time taken = %lf\n",t);

    return 0;
}