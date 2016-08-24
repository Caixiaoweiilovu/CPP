
#include "cv.h"
#include "highgui.h"
#include "Image.h"
#include "Matrix.h"
#include<iostream>
#include<ctime>

using namespace std;

void Matrix::Alloc(int h,int w)
{
    data=new double*[h];
    for(int i=0;i<h;i++)
    {
        data[i]=new double[w];
        for(int j=0;j<w;j++)
            data[i][j]=NULL;
    }
}
void Matrix::Release()
{
	if (data != NULL)
	{
		for (int i = 0;i < height;i++)
			delete[] data[i];
		delete [] data;
	}
	height = 0;
	width = 0;
	data = NULL;
}
void Matrix::Release(unsigned char ***d, int h)
{
	for (int i = 0; i < h; i++)
		delete[] (*d)[i];
	delete[] (*d);
	*d = NULL;
}
Matrix::Matrix():height(0),width(0),data(NULL){}

Matrix::Matrix(int h, int w):height(h),width(w)
{
    Alloc(h,w);
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            data[i][j]=0;
}

Matrix::Matrix(int h, int w, double val)
{
    Alloc(h,w);
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            data[i][j]=val;
}

Matrix::Matrix(const Matrix &m)
{
    height=m.height;
    width=m.width;
    data=m.data;
}

Matrix::~Matrix()
{
    for(int m=0;m<height;m++)
        delete[]data[m];
    delete[]data;
}

void Matrix::Zeros(int h, int w) {Matrix(h,w);}// ���ݲ�������h��w�е�ȫ�����

void Matrix::Ones(int h, int w) {Matrix(h,w,1);}// ���ݲ�������h��w�е�ȫ1����

void Matrix::Random(int h, int w) 
{
    Alloc(h,w);
    srand(time(NULL));
    for(int i=0;i<h;h++)
        for(int j=0;j<w;j++)
            data[i][j]=(double)(rand()%100)/100;
    Release();
}//����h��w�е�������󣬾����Ԫ��Ϊ[0,1]֮������ʵ����double���ͣ�

void Matrix::Identity(int n)
{
    Matrix(n,n);
    for(int i=0;i<n;i++)
        data[i][i]=1;
}// ���ݲ�������n��n�еĵ�λ����

int Matrix::Height(){return height;}// ��þ��������

int Matrix::Width(){return width;}// ��þ��������

Matrix Matrix::MajorDiagonal()
{
    Matrix m;
    int N;
    if(height==width)
        N=width;
    else
        cout<<"������Ĳ��Ƿ���"<<endl;
    m.data=new double *[N];
    for(int i=0;i<N;i++){
       m.data[i]=new double[1];
        for(int j=0;j<N;j++)
           m.data[i][1]=data[j][j];
    }
    return m;
}// ��������Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ���Ԫ�صĸ���

Matrix Matrix::MinorDiagonal(){ 
    Matrix m;
    int N;
    if(height==width)
        N=width;
    else
        cout<<"������Ĳ��Ƿ���"<<endl;
    m.data=new double *[N];
    for(int i=0;i<N;i++){
       m.data[i]=new double[1];
        for(int j=0;j<N;j++)
            m.data[i][1]=data[j][N-j];}
    return m;
    Release();
}// �����ĸ��Խ����ϵ�Ԫ�أ����һ��N��1�еľ���NΪ���Խ�����Ԫ�صĸ���

Matrix Matrix::Row(int n){
    Matrix m;
    int N=width;
    m.data=new double *[1];
    for(int i=0;i<1;i++){
       m.data[i]=new double[N];
        for(int j=0;j<N;j++)
            m.data[1][j]=data[n][j];}
    return m;
    Release();
}// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��1��N�еľ��������NΪ��n����Ԫ�صĸ���

Matrix Matrix::Column(int n){
    Matrix m;
    int N=height;
    m.data=new double *[N];
    for(int i=0;i<N;i++){
       m.data[i]=new double[N];
        for(int j=0;j<1;j++)
            m.data[j][1]=data[j][n];}
    return m;
    Release();}// ���ؾ���ĵ�n���ϵ�Ԫ�أ����һ��N��1�еľ��������NΪ��n����Ԫ�صĸ���

void Matrix::Transpose()
{
    Matrix m;
    int n;
    if(height>width) n=height;
    else n=width;
    Alloc(n,n);
    for(int i=0;i<width;i++){
        m.data[i]=new double[width];
        for(int j=0;j<height;j++)
            m.data[i][j]=data[j][i];}
    for(int p=0;p<width;p++)
        for(int q=0;q<height;q++)
            data[p][q]=m.data[p][q];
    Release();
}// ������ת��

double & Matrix::At(int row, int col){
    return data[row][col];}//��ȡ��row�е�col�еľ���Ԫ�ص�ֵ

void Matrix::Set(int row, int col, double value){
    data[row][col]=value;}//���õ�row�е�col�о���Ԫ�ص�ֵΪvalue

void Matrix::SetAll(double value){
    	for(int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
            data[i][j] = value;} //���þ�������Ԫ��Ϊͬһֵvalue

void Matrix::Reshape(int h, int w){
   	if(height * width != h * w)
    {
        cout<<"Ԫ�ظ��������"<<endl;
    }
    else
    {
		int i = 0;
		int j = 0;
       double **dataturn = new double* [h];
       for(i = 0; i < h; i++)
       {
           *(dataturn + i) = new double [w];
       }
       int p = 0;
       int q = 0;
       int num = 0;
       for(i = 0; i < h; i++)
       {
          for(j = 0; j < w; j++, q++)
          {
              dataturn[i][j] = data[p][q];
              num++;
              if(num % width == 0)
              {
                  p++;
                  q = -1;
              }
          }
       }
       double **temp = NULL;
       temp = data;
       data = dataturn;
       dataturn = temp;
       for(i = 0; i < height; i++)
       {
           delete []*(dataturn+i);
       }
       delete []dataturn;
       dataturn = NULL;
       height = h;
       width = w;
    } 
    Release();
 } //�ھ���Ԫ���������������£����������б�Ϊ���������Ĵ�С

bool Matrix::IsEmpty(){
    if(height == 0 && width == 0)
        return true;
    else
        return false;
    }
            // �жϾ����Ƿ�Ϊ�վ���
bool Matrix::IsSquare(){
    if(height==width)
        return true;
    else 
        return false;}// �жϾ����Ƿ�Ϊ����
void Matrix::CopyTo(Matrix &m){
    int i = 0;
    int j = 0;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            *(*(m.data + i) + j) = data[i][j];
        }
    }
    m.height = height;
    m.width = width;
}// �������Ƹ�m
void Matrix::Mul(double s){
    int i = 0;
    int j = 0;
    int val = 0;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            val = data[i][j] * s;
            if(val >255)
            {
                data[i][j] = 255;
            }
            else
            {
                if(val < 0)
                {
                    data[i][j] = 0;
                }
                else
                {
                     data[i][j] = data[i][j] * s;
                }
            }
        }
    }
}// �����ÿ��Ԫ�ض����Բ���

void Matrix::Cat(Matrix &m, int code){
    if(code)  //ƴ�ӵ��ұ�
    {
        if(height != m.height)
        {
            cout<<"�߶Ȳ�ƥ�䣬����ƴ��"<<endl;
        }
        else
        {
            int i = 0;
            int j = 0;
            int w = 0;
            
            double** dataturn = new double* [height];
            for(i = 0; i < height; i++)
            {
                *(dataturn + i) = new double [width + m.width];
            }
            for(i = 0; i < height; i++)
            {
                for(j = 0; j < (width + m.width); j++)
                {
                    if(j >= width)
                    {   
                        dataturn[i][j] = m.data[i][w++];
                        if(w % m.width == 0)
                        {
                           w = 0;
                        }
                    }
                    else
                    {
                        dataturn[i][j] = data[i][j];
                    }
                }
            }
            double** temp = NULL;
            temp = data;
            data = dataturn;
            dataturn = temp;
            for(i = 0; i < height; i++)
            {
                delete []*(dataturn + i);
            }
            delete []dataturn;
            dataturn = NULL;
            width = width + m.width;
        }
    }
    else  //ƴ�ӵ�����
    {
        if(width != m.width)
        {
            cout<<"��Ȳ�ƥ�䣬����ƴ��"<<endl;
        }
        else
        {
            int i = 0;
            int j = 0;
            int w = 0;
            int num = 0;
            double** dataturn = new double* [height + m.height];
            for(i = 0; i < height + m.height; i++)
            {
                *(dataturn + i) = new double [width];
            }
            for(i = 0; i < height + m.height; i++)
            {
                for(j = 0; j < width; j++)
                {
                    if(i >= height)
                    {
                        dataturn[i][j] = m.data[w][j];
                        num = j + 1;
                        if(num % m.width == 0)
                        {
                            w++;
                        }

                    }
                    else
                    {
                        dataturn[i][j] = data[i][j];
                    }
                }
            }
            double** temp = NULL;
            temp = data;
            data = dataturn;
            dataturn = temp;
            for(i = 0; i < height; i++)
            {
                delete []*(dataturn + i);
            }
            delete []dataturn;
            dataturn = NULL;
            height = height + m.height;
        }
    }
    Release();
}
// ������m�뵱ǰ�������ƴ�ӣ�code����ƴ�ӵķ�ʽ����mƴ��

Matrix Add(const Matrix &m1, const Matrix &m2)
{
	if((m1.height != m2.height) || (m1.width != m2.width))
    {
        cout<<"���в��ȣ��������"<<endl;
        return Matrix(0, 0);
    }
    else 
    {
        int sum = 0;
        Matrix m0(m1.height, m1.width);
        m0.height = m1.height;
        m0.width = m1.width;
        for(int i = 0; i < m1.height; i++)
        {
            for(int j = 0; j < m1.width; j++)
            {
                sum = m1.data[i][j] + m2.data[i][j];
                if(sum > 255)
                {
                    m0.data[i][j] = 255;
                }
                else
                {
                    if(sum < 0)
                    {
                        m0.data[i][j] = 0;
                    }
                    else
                    {
                        m0.data[i][j] = sum;
                    }
                }
            }
        }
		return m0;
    }
}
// ��Ԫ������������m1��m2��������������Ϊ�����ķ���ֵ
Matrix Sub(const Matrix &m1, const Matrix &m2)
{
	 if((m1.height != m2.height) || (m1.width != m2.width))
    {
        cout<<"���в��ȣ��������"<<endl;
        return Matrix(0, 0);
    }
    else 
    { 
        int sub = 0;
        Matrix m0(m1.height, m1.width);
        for(int i = 0; i < m1.height; i++)
        {
            for(int j = 0; j < m1.width; j++)
            {
                sub = m1.data[i][j] - m2.data[i][j];
                if(sub > 255)
                {
                    m0.data[i][j] = 255;
                }
                else
                {
                    if(sub < 0)
                    {
                       m0.data[i][j] = 0;
                    }
                    else
                    {
                        m0.data[i][j] = sub;
                    }
                }
            }
        }
	    return m0;
    }
}
// ��Ԫ������������������
void Swap(Matrix &a, Matrix &b)
{
	int t = a.height;
	a.height = b.height;
	b.height = t;

	t = a.width;
	a.width = b.width;
	b.width = t;

	double **p = a.data;
	a.data = b.data;
	b.data = p;
}

