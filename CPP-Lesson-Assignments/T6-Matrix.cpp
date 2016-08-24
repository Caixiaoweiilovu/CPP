
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

void Matrix::Zeros(int h, int w) {Matrix(h,w);}// 根据参数产生h行w列的全零矩阵

void Matrix::Ones(int h, int w) {Matrix(h,w,1);}// 根据参数产生h行w列的全1矩阵

void Matrix::Random(int h, int w) 
{
    Alloc(h,w);
    srand(time(NULL));
    for(int i=0;i<h;h++)
        for(int j=0;j<w;j++)
            data[i][j]=(double)(rand()%100)/100;
    Release();
}//产生h行w列的随机矩阵，矩阵的元素为[0,1]之间的随机实数（double类型）

void Matrix::Identity(int n)
{
    Matrix(n,n);
    for(int i=0;i<n;i++)
        data[i][i]=1;
}// 根据参数产生n行n列的单位矩阵

int Matrix::Height(){return height;}// 获得矩阵的行数

int Matrix::Width(){return width;}// 获得矩阵的列数

Matrix Matrix::MajorDiagonal()
{
    Matrix m;
    int N;
    if(height==width)
        N=width;
    else
        cout<<"您输入的不是方阵。"<<endl;
    m.data=new double *[N];
    for(int i=0;i<N;i++){
       m.data[i]=new double[1];
        for(int j=0;j<N;j++)
           m.data[i][1]=data[j][j];
    }
    return m;
}// 求矩阵主对角线上的元素，输出一个N行1列的矩阵，N为主对角线元素的个数

Matrix Matrix::MinorDiagonal(){ 
    Matrix m;
    int N;
    if(height==width)
        N=width;
    else
        cout<<"您输入的不是方阵。"<<endl;
    m.data=new double *[N];
    for(int i=0;i<N;i++){
       m.data[i]=new double[1];
        for(int j=0;j<N;j++)
            m.data[i][1]=data[j][N-j];}
    return m;
    Release();
}// 求矩阵的副对角线上的元素，输出一个N行1列的矩阵，N为副对角线上元素的个数

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
}// 返回矩阵的第n行上的元素，组出一个1行N列的矩阵输出，N为第n行上元素的个数

Matrix Matrix::Column(int n){
    Matrix m;
    int N=height;
    m.data=new double *[N];
    for(int i=0;i<N;i++){
       m.data[i]=new double[N];
        for(int j=0;j<1;j++)
            m.data[j][1]=data[j][n];}
    return m;
    Release();}// 返回矩阵的第n列上的元素，组出一个N行1列的矩阵输出，N为第n列上元素的个数

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
}// 将矩阵转置

double & Matrix::At(int row, int col){
    return data[row][col];}//获取第row行第col列的矩阵元素的值

void Matrix::Set(int row, int col, double value){
    data[row][col]=value;}//设置第row行第col列矩阵元素的值为value

void Matrix::SetAll(double value){
    	for(int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
            data[i][j] = value;} //设置矩阵所有元素为同一值value

void Matrix::Reshape(int h, int w){
   	if(height * width != h * w)
    {
        cout<<"元素个数不相等"<<endl;
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
 } //在矩阵元素总数不变的情况下，将矩阵行列变为参数给定的大小

bool Matrix::IsEmpty(){
    if(height == 0 && width == 0)
        return true;
    else
        return false;
    }
            // 判断矩阵是否为空矩阵
bool Matrix::IsSquare(){
    if(height==width)
        return true;
    else 
        return false;}// 判断矩阵是否为方阵
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
}// 将矩阵复制给m
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
}// 矩阵的每个元素都乘以参数

void Matrix::Cat(Matrix &m, int code){
    if(code)  //拼接到右边
    {
        if(height != m.height)
        {
            cout<<"高度不匹配，不可拼接"<<endl;
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
    else  //拼接到下面
    {
        if(width != m.width)
        {
            cout<<"宽度不匹配，不可拼接"<<endl;
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
// 将矩阵m与当前矩阵进行拼接，code代表拼接的方式：将m拼接

Matrix Add(const Matrix &m1, const Matrix &m2)
{
	if((m1.height != m2.height) || (m1.width != m2.width))
    {
        cout<<"行列不等，不可相加"<<endl;
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
// 友元函数，将矩阵m1和m2相减，结果矩阵作为函数的返回值
Matrix Sub(const Matrix &m1, const Matrix &m2)
{
	 if((m1.height != m2.height) || (m1.width != m2.width))
    {
        cout<<"行列不等，不可相减"<<endl;
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
// 友元函数，交换两个矩阵
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

