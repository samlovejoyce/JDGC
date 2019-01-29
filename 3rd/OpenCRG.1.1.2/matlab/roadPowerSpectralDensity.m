%% 公路谱密度计算函数
%   返回值：
%   参数1:v表示车辆行驶速度，单位m/s
%   参数2:level表示要生成公路等级的常数项，取值范围是整型数[1-8]
%   参数3:N表示采样点数量
%%
function[data] = roadPowerSpectralDensity(v, level, N)
%%
% data:返回值 
%   v:速度
%   fmin:时间频率的最小值，可以设为固定量（0.5）
%   fmax:时间频率的最大值，可以设为固定量（30）
%       fmin,fmax表示的是时间频率，其单位是Hz。 f = n * v,就是时间频率等于空间频率乘以速度
%   Gd0:公路谱密度常数项分为A-H8个等级，Gd0是计算Gd值公式中的一个常数 (2^N,N = 4,6,8,10,12,14,16,18)
%   N:采样点数量
%   fs:采样频率，需要满足：fs > 2 * fmax
%%

%v=1;
fmin=0.5;								%时间频率 Hz
fmax=30;								%时间频率 Hz

nmin=fmin/v;        					%空间频率 = fmin/v;
nmax=fmax/v;                			%空间频率 = fmax/v;

%% 公路等级常量,Gd0是计算Gd值公式中的一个常数 (2^N,N = 4,6,8,10,12,14,16,18)
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

%N=2^14;                					%采样点数
fs=200;                					%采样频率

%%
deltf=fs/N;                				%时间域_频率分辨率
deltt=1/fs;                				%采样时间间隔
deltl=deltt*v;        					%采样距离间隔

deltf_r=deltf/v;                		%空间-频率分辨率

Neff=(nmax-nmin)/deltf_r;        		%有效频段内的采样点数
N0=nmin/deltf_r;        				%需要满足条件(N0+Neff<N/2)

k=0;
while(k*deltf_r<nmin)
k=k+1; 									%判断下截止频率所在位置
end

l=0;
while(l*deltf_r<nmax)
l=l+1; 									%判断上截止频率所在位置
end

Gd=[];									%Gd表示路面功率谱密度函数
x=[];

for ii=1:k
Gd(ii)=0;
x(ii)=0;
end

%%
% w为频率指数，为双对数坐标上斜线的频率，决定路面功率谱密度的频率结构
%%
w = 2;
for ii=k+1:1:l+1
Gd(ii)=Gd0*((ii-1)*deltf_r/0.1)^(-w);    %空间频率下的功率谱
x(ii)=sqrt(N*Gd(ii)/2/deltl);            %频谱幅值
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

xc(N/2+2:N)=fliplr(conj(xc(2:N/2)));     %共轭对称

xifft=ifft(xc);

for j=1:N
t(j)=(j-1)*deltl;
end

xaver=mean(xifft);
xsd=std(xifft);
xmax=max(xifft);

%% 数据返回
data.xifft = xifft;
data.i = t;
data.length = N;
