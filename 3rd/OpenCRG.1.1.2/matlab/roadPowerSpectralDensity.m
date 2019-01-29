%% ��·���ܶȼ��㺯��
%   ����ֵ��
%   ����1:v��ʾ������ʻ�ٶȣ���λm/s
%   ����2:level��ʾҪ���ɹ�·�ȼ��ĳ����ȡֵ��Χ��������[1-8]
%   ����3:N��ʾ����������
%%
function[data] = roadPowerSpectralDensity(v, level, N)
%%
% data:����ֵ 
%   v:�ٶ�
%   fmin:ʱ��Ƶ�ʵ���Сֵ��������Ϊ�̶�����0.5��
%   fmax:ʱ��Ƶ�ʵ����ֵ��������Ϊ�̶�����30��
%       fmin,fmax��ʾ����ʱ��Ƶ�ʣ��䵥λ��Hz�� f = n * v,����ʱ��Ƶ�ʵ��ڿռ�Ƶ�ʳ����ٶ�
%   Gd0:��·���ܶȳ������ΪA-H8���ȼ���Gd0�Ǽ���Gdֵ��ʽ�е�һ������ (2^N,N = 4,6,8,10,12,14,16,18)
%   N:����������
%   fs:����Ƶ�ʣ���Ҫ���㣺fs > 2 * fmax
%%

%v=1;
fmin=0.5;								%ʱ��Ƶ�� Hz
fmax=30;								%ʱ��Ƶ�� Hz

nmin=fmin/v;        					%�ռ�Ƶ�� = fmin/v;
nmax=fmax/v;                			%�ռ�Ƶ�� = fmax/v;

%% ��·�ȼ�����,Gd0�Ǽ���Gdֵ��ʽ�е�һ������ (2^N,N = 4,6,8,10,12,14,16,18)
Gd0 = 0;
switch(level)
    case 1
        Gd0 = 2^4;
    case 2
        Gd0 = 2^6;
    case 3
       Gd0 = 2^8;
    case 4
        Gd0 = 2^10;
    case 5
        Gd0 = 2^12;
    case 6
        Gd0 = 2^14;
    case 7
        Gd0 = 2^16;
    case 8
        Gd0 = 2^18;
end

%N=2^14;                					%��������
fs=200;                					%����Ƶ��

%%
deltf=fs/N;                				%ʱ����_Ƶ�ʷֱ���
deltt=1/fs;                				%����ʱ����
deltl=deltt*v;        					%����������

deltf_r=deltf/v;                		%�ռ�-Ƶ�ʷֱ���

Neff=(nmax-nmin)/deltf_r;        		%��ЧƵ���ڵĲ�������
N0=nmin/deltf_r;        				%��Ҫ��������(N0+Neff<N/2)

k=0;
while(k*deltf_r<nmin)
k=k+1; 									%�ж��½�ֹƵ������λ��
end

l=0;
while(l*deltf_r<nmax)
l=l+1; 									%�ж��Ͻ�ֹƵ������λ��
end

Gd=[];									%Gd��ʾ·�湦�����ܶȺ���
x=[];

for ii=1:k
Gd(ii)=0;
x(ii)=0;
end

%%
% wΪƵ��ָ����Ϊ˫����������б�ߵ�Ƶ�ʣ�����·�湦�����ܶȵ�Ƶ�ʽṹ
%%
w = 2;
for ii=k+1:1:l+1
Gd(ii)=Gd0*((ii-1)*deltf_r/0.1)^(-w);    %�ռ�Ƶ���µĹ�����
x(ii)=sqrt(N*Gd(ii)/2/deltl);            %Ƶ�׷�ֵ
end

for ii=l+2:1:N/2
Gd(ii)=0;
x(ii)=0;
end

Gd(N/2+1)=0;
x(N/2+1)=0;

a=[];
xc=zeros(1,N);
for j=1:N/2
a(j)=2*pi*rand();
b(j)=cos(a(j))+i*sin(a(j));
xc(j)=b(j).*x(j);
end

xc(N/2+2:N)=fliplr(conj(xc(2:N/2)));     %����Գ�

xifft=ifft(xc);

for j=1:N
t(j)=(j-1)*deltl;
end

xaver=mean(xifft);
xsd=std(xifft);
xmax=max(xifft);

%% ���ݷ���
data.xifft = xifft;
data.i = t;
data.length = N;
