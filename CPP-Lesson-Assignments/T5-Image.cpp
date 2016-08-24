#include "cv.h"
#include "highgui.h"
#include "Image.h"
#include<iostream>
using namespace std;

//���캯��
Image::Image():height(0),width(0),data(NULL){}
//���캯������
Image::Image(int h, int w):height(h),width(w)
{
    data=new unsigned char*[h];
    for(int i=0;i<h;i++)
    {
        data[i]=new unsigned char[w];
        for(int j=0;j<w;j++)
            data[i][j]=0;
    }
}
Image::Image(int h, int w, unsigned char val)
{
    data=new unsigned char*[h];
    for(int i=0;i<h;i++)
    {
        data[i]=new unsigned char[w];
        for(int j=0;j<w;j++)
            data[i][j]=val;
    }
}
Image::Image(char* ImageName)
{
    Read(ImageName);
}
Image::Image(unsigned char *m, int rows, int cols)
{
    height=rows;
    width=cols;
    data=new unsigned char*[height];
    for(int i=0;i<height;i++)
    {
        data[i]=new unsigned char[width];
        for(int j=0;j<width;j++)
            data[i][j]=m[i*cols+j];
    }
}
Image::Image(unsigned char m[][100], int rows)
{
    height=rows;
    width=100;
    data=new unsigned char*[height];
    for(int i=0;i<height;i++)
    {
        data[i]=new unsigned char[width];
        for(int j=0;j<width;j++)
            data[i][j]=m[i][j];
    }
}
Image::Image(unsigned char **m, int h, int w)
{
    width=w;
    height=h;
    data=m;
}
//�������캯��
Image::Image(const Image &im)
{
    height=im.height;
    width=im.width;
    data=im.data;
}

//��������
Image::~Image()
{
    for(int m=0;m<height;m++)
        delete[]data[m];
    delete[]data;
}

//��Ӳ�̶���ͼ���ļ�; 
void Image::Read(char* ImageName)
{
	IplImage* img = cvLoadImage(ImageName, CV_LOAD_IMAGE_GRAYSCALE);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;
    //��һάָ��img_dataָ����ڴ��е�ֵд���Ա������άָ��data��ָ���ڴ���
    height = img->height;
	width = img->width;
	if (data != NULL){
		for (int i = 0; i < height; i++)
			delete [] data[i];
		delete [] data;
	}
	data = new unsigned char *[height];
	int y = 0;
	for (int x = 0; x < height; x++)
		data[x] = new unsigned char [widthstep];
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			data[i][j] = img_data[y];
			y++;
		}
	}
cvReleaseImage(&img);
}

//����ͼ��; 
void Image::Write(unsigned char *src, int w, int h, unsigned char **b)  //��ͼ�����ݱ���Ϊͼ���ļ�
{
	IplImage* img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;
	int a = 0;
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			src[a] = b[i][j];
			a++;
		}
	}
	cvReleaseImage(&img);
}

//��ʾͼ��;
void Image::Show(char *winname)
{
	IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	unsigned char *img_data = (unsigned char *)(img->imageData);
	int widthstep = img->widthStep;
      
    int m=0;//��data��ָ�ڴ��е�ֵд��img_data��ָ���ڴ�
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {img_data[m]=data[i][j];m++;}

	cvNamedWindow(winname, CV_WINDOW_AUTOSIZE);//��������
    cvShowImage(winname, img);
	cvWaitKey(0);
	cvReleaseImage(&img); //�ͷ�ͼ��;
}

//��ȡͼ����ָ�����ֵ
unsigned char& Image::At(int row, int col)
{
    return data[row][col];
}

void Image::Set(int row, int col, unsigned char value)  //��������(row,col)Ϊĳֵ
{
	data[row][col] = value;
}

void Image::SetAll(unsigned char value)  //����ͼ��Ϊͬһֵ
{
	Read("Airplane.jpg"); 
	for(int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			data[i][j] = value;
	Show("Image");
}

//false ���ң�true ����;
void Image::Flip(int code) 
{
   Read("Fruits.jpg");
   if(code)
    {
        unsigned char b;
        for(int p=0,q=height-1;p<height/2;p++,q--)
        {
            for(int r=0;r<width;r++)
            {
            b=data[p][r];
			data[p][r]=data[q][r];
            data[q][r]=b;
            }
        }
    }
    else
    { 
        unsigned char a;
	    for(int i=0,j=width-1;i<width/2;i++,j--)
        {
            for(int k=0;k<height;k++)
            {
            a=data[k][i];
			data[k][i]=data[k][j];
            data[k][j]=a;
            }
        }  
    }	Show("Image");
}
//ͼ����С���Ŵ�
void Image::Resize(int code)
{
    	Read("Fruits.jpg");
        if(code)
        {
        int p=0,q=0;
        unsigned char **x=new unsigned char *[height*2];
        for(int m=0;m<(height*2);m++)
        {*(x+m)=new unsigned char [width*2];}
        for(int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
            {
                x[p][q] = data[i][j];
			    x[p][q+1] = data[i][j];
			    q += 2;
			    x[p+1][q] = data[i][j];
			    x[p+1][q+1] = data[i][j];
                if (q== width*2){p += 2;q = 0;}
            }
        }	
        IplImage *img2 = cvCreateImage(cvSize(width*2, height*2), IPL_DEPTH_8U, 1);
	    unsigned char *img2_data = (unsigned char *)(img2->imageData);
	    Write(img2_data, width*2, height*2, x);
	    cvShowImage("Image", img2);
        cvWaitKey(0);
    }

    else
    {
        unsigned char **y=new unsigned char *[height/2];
        for(int n=0;n<(height/2);n++)
        {*(y+n)=new unsigned char [width/2];}
        for(int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
            {
                if(i%2==1&&j%2==1)
                {y[(i-1)/2][(j-1)/2]=data[i][j];}
            }
        }
        IplImage *img2 = cvCreateImage(cvSize(width/2, height/2), IPL_DEPTH_8U, 1);
	    unsigned char *img2_data = (unsigned char *)(img2->imageData);
	    Write(img2_data, width/2, height/2, y);
	    cvShowImage("Image", img2);
        cvWaitKey(0);
    }
}

//ͼ��ü��ĺ���
void Image::Cut(int x1,int y1,int x2,int y2)
{
    Read("Fruits.jpg");
    int p=0,q=0,mid;
    if(x1>x2){mid=x1;x1=x2;x2=mid;}
    if(y1>y2){mid=y1;y1=y2;y2=mid;}
    unsigned char **a=new unsigned char *[height];
    for(int n=0;n<height;n++)
    {*(a+n)=new unsigned char [width];}
    for (int i = x1; i <= x2; i++)
    {
		for (int j = y1; j <= y2; j++)
        {
			a[p][q] = data[i][j];
			q++;
		    if (j == y2)
            {
				p++;
			    q = 0;
			}
		}
    }
    IplImage *img3 = cvCreateImage(cvSize(x2-x1, y2-y1), IPL_DEPTH_8U, 1);
	unsigned char *img3_data = (unsigned char *)(img3->imageData);
	Write(img3_data, x2-x1, y2-y1, a);
	cvShowImage("Image", img3);
    cvWaitKey(0);
}
//ͼ����ת�ĺ���
void Image::Rotate(int degree)
{
    Read("Fruits.jpg");
    int h=height,w=width,m;
    if(height>width) {m=height;}
    else {m=width;}

    unsigned char **a=new unsigned char *[m];
    for(int n=0;n<m;n++)
    {*(a+n)=new unsigned char [m];}

    switch((degree/4)%4)
    {
    case 0:
        a=data;break;
    case 1:
        {
            for (int i = 0; i < height; i++)
            {
			for (int j = 0; j < width; j++)
				a[width-j][i] = data[i][j];
            }
            break;
        }
    case 2:
        {	
           	unsigned char temp;
		    for (int i = 0; i < height/2; i++)
            {
			for (int j = 0; j < width; j++)
            {
				temp = data[i][j];  
                data[i][j] = data[height-1-i][j];  
                data[height-1-i][j] = temp;    
			}  
            }
		for (i = 0; i < height; i++)
        {
			for (int j = 0; j < width/2; j++)
            {
				temp = data[i][j];  
                data[i][j] = data[i][width-1-j];  
                data[i][width-1-j] = temp;    
			}  
		} 
		for (i = 0; i < height; i++)
        {
			for (int j = 0; j < width; j++)
            {
				a[i][j]=data[i][j];
			}
		}
           break;
        }
    case 3:
        {
            for(int p=0;p<width;p++)
            {
            w=w-1;
            for(int q=0;q<height;q++)
                a[p][q]=data[q][w];
            }
            break;
        }
    default:
        cout<<"����Ķ������Ϸ���"<<endl;
        break;
    }
    if (degree/90 == 1 || degree/90 == 3){
		IplImage *img3 = cvCreateImage(cvSize(height, width), IPL_DEPTH_8U, 1);
	    unsigned char *img3_data = (unsigned char *)(img3->imageData);
	    Write(img3_data, height, width, a);
	    cvShowImage("Image", img3);
        cvWaitKey(0);
	}
	if (degree/90 == 2 || degree/90 == 4){
		IplImage *img3 = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	    unsigned char *img3_data = (unsigned char *)(img3->imageData);
	    Write(img3_data, width, height, a);
	    cvShowImage("Image", img3);
        cvWaitKey(0);
	}
}
//��ͼ��ľ�ֵ�ͷ�����ò������
void Image::Mean_Variance(float &m, float &var)
{	Read("Fruits.jpg"); 
    float sum = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			sum+=(float) data[i][j];
	m = sum / (width * height);
	for ( i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			sum = sum + ((float) data[i][j] - m) * ((float) data[i][j] - m);
	var = sum / (width * height);
    cout << "ͼ��ľ�ֵΪ��"<< m <<endl<< "ͼ��ķ���Ϊ��" << var << endl;
 }
//ʵ����Ԫ��������������Image���������
void Swap(Image &a, Image &b)
{
    int k=0;
    unsigned char**c=NULL;
    k=a.height;
    a.height=b.height;
    b.height=k;
    k=a.width;
    a.width=b.height;
    c=a.data;
    a.data=b.data;
    b.data=c;
}
