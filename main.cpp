/***********************************************/
/*       Author: Majed Alshaikhhussain         */
/*           p03: Composite Bitmap             */
/***********************************************/

#include <iostream>
#include "bitmap.h"
#include <cstring>

using namespace std;
/* Function that recives a file name and width & hight 
   of the base image (by value) and validate the image
   whether it is exist or not, whether it is the
   same size or not.
   */ 
bool validatImage(string fn, int w, int h);
/* Function that recives the image as a Pixels (by reference)
   an image from the list of images that we have. compose
   two and return nothing.
   */ 
void composite(vector<vector<Pixel> > &bmpImage, Bitmap img);


int main(int argc, char *argv[])
{

  string fileName;	//variable to hold the file name
  int counter = 0;	//variable to hold the number of valid images
  Bitmap image[10];	//vector of images of type Bitmap to hold the images
  vector<vector<Pixel> > bmp;	//two diminstion vector to hold the image pixels
  int width,hight;		//to hold width and hight of base image


  /*repeatedly asking the user to give input of filename
    until maximum number is reached or the user types DONE*/
  while(counter<10){

    cout<<"Enter name of image, should be a valid BMP with 24bit color depth:"<<endl;
    cin>>fileName;
    /*check if the user entered done exit the loop*/
    if((fileName=="DONE") || (fileName=="done")){
      break;
    }
    /*if we are reading first image then check if it is valid or not
      then save the width and hight of image if it is valid to 
      use it as reference for the rest of the images*/
    else if(counter==0){
      image[0].open(fileName);
      if(image[0].isImage()){
        bmp = image[0].toPixelMatrix();
        width=bmp.size();
        hight=bmp[0].size();
        counter+=1;
      }
      else{
        cout<<"The file doesn't exist or isn't a valid bitmap."<<endl;
      }
    }
    /*validate the rest of images other than the first image*/
    else{
      if(validatImage(fileName,width,hight)){
        image[counter].open(fileName);
        counter+=1;
      }
    }

  }
  /*printing an error message if the user didn't provide
    at least two files with the same dimensions*/
  if(counter <2)
  {
    cout<<"Composite image cannot be created."<<endl;
  }
  else
  {
    cout<<"image "<<1<<" of "<<counter<< " is done."<<endl;
    for(int i=1; i<counter; i++){
      composite(bmp, image[i]);
      cout<<"Image "<<i+1<<" of "<<counter<< " is done."<<endl;
    }
    /*convert the composed image back into Bitmap and save it*/
    image[0].fromPixelMatrix(bmp);
    image[0].save("composite-Malshaikhhussain.bmp");//composite image*/
  }
  return 0;
}

bool validatImage(string fn, int w, int h){
  Bitmap Btemp;
  vector<vector<Pixel> > temp;
  Btemp.open(fn);
  /*ensuring that the image is valide and has the same
    dimensions(width and height) as the first image loaded*/
  if(Btemp.isImage())
  {
    temp = Btemp.toPixelMatrix();
    if(temp.size()!=w || temp[0].size()!=h){
      cout<<"The file is NOT the same dimensions as the first image loaded"<<endl;
      return false;
    }
    return true;
  }
  cout<<"The file doesn't exist or isn't a valid bitmap."<<endl;
  return false;
}


void composite(vector<vector<Pixel> > &bmpImage, Bitmap img){
  vector<vector<Pixel> > temp;
  temp=img.toPixelMatrix();
  /*compose the two images by taking the averge for each pixel color*/
  for(int j=0; j<temp.size();j++)
    for(int k=0; k<temp[j].size(); k++){
      bmpImage[j][k].red=(temp[j][k].red+bmpImage[j][k].red)/2;
      bmpImage[j][k].green=(temp[j][k].green+bmpImage[j][k].green)/2;
      bmpImage[j][k].blue=(temp[j][k].blue+bmpImage[j][k].blue)/2;
    }
}
