% DEFAULT SETTINGS
% clear enviroment
clear all;
close all
% display results
dispRes = 0;


% build minimum crg-struct
uinc = 0.01;
vinc = 0.01;
warn_cnt = 0;
txtnum   = 0;

%% Mathod 1
nv = 201;
nu = 5*nv;
ubeg = 0;
uend = nu;

v = -(nv-1)/2*vinc:vinc:(nv-1)/2*vinc;
inc = uinc;
u = nu;

%%
z = peaks(nv);
z = repmat(z, nu/nv, 1);

data.u = (nu-1)*uinc;
data.v = (nv-1)*vinc/2;
data.z = z;
data.ct{1} = 'CRG defined by z matrix';


%% curvature
% select or deselect for test purposes as shown below

LC1  = 10;  R1s  = inf;  R1e  = inf;
LC2  = 30;   R2s  = inf;  R2e  = 50;
LC3  = 20;  R3s  = 50;   R3e  = 50;

c = { LC1   {1/R1s  ( 1/R1e  - 1/R1s )/LC1 }  ...
    ; LC2   {1/R2s  ( 1/R2e  - 1/R2s )/LC2 }  ...
    ; LC3   {1/R3s  ( 1/R3e  - 1/R3s )/LC3 }  ...
    % ; LC31  {1/R31s ( 1/R31e - 1/R31s)/LC31}  ...
%     ; LC4   {1/R4s  ( 1/R4e  - 1/R4s )/LC4 }  ...
%     ; LC5   {1/R5s  ( 1/R5e  - 1/R5s )/LC5 }  ...
    };

% simple check of curvature data
csum = 0;
for ii = 1:size(c,1)
    len = c{ii,1};
    if len < 0 || ~isequal(rem(len,uinc), 0)            % todo: bound should be greater 0, ask => jorauh
        warning('CRG:checkWarning', [num2str(ii) '. length = ' curvatue num2str(len) ' is negative and/or mismatch with increment of u.  => fatal']);
        err_cnt = err_cnt + 1;
    end
    csum = csum + len;
    % maybe a check greater than (uend-ubeg) is useful
end
c = [ c; { max(0,(uend-ubeg)-csum) {0} } ];    % if required add straight line up to the end
txtnum = txtnum + 1; data.ct{txtnum} = '... curvature added';

%% slope
% select or deselect for test purposes as shown below

LS1  = 10;   S1s  =  0.0;    S1e  =  0.0;
LS2  = 30;  S2s  =  0.0;    S2e  =  0.01;
LS3  = 40;  S3s  =  0.01;  S3e  =  0.01;

s = { LS1   { S1s ( S1e  - S1s )/LS1 }  ...
    ; LS2   { S2s ( S2e  - S2s )/LS2 }  ...
    ; LS3   { S3s ( S3e  - S3s )/LS3 }  ...
    };

% simple check of slope data
ssum = 0;
for ii = 1:size(s,1)
    len = s{ii,1};
    if len < 0 || ~isequal(rem(len,uinc), 0)            % todo: bound should be greater 0, ask => jorauh
        warning('CRG:checkWarning', [ num2str(ii) '. slope length = ' num2str(len) ' is negative and/or mismatch with increment of u. => fatal']);
        err_cnt = err_cnt + 1;
    end
    ssum = ssum + len;
    % maybe a check greater than (uend-ubeg) is useful
end
s = [ s; { max(0,(uend-ubeg)-ssum) {0} } ];    % if required keep last value up to the end
txtnum = txtnum + 1; data.ct{txtnum} = '... slope added';

%% banking
% select or deselect for test purposes as shown below

LB1  = 10;  B1s  =  0;     B1e  = 0;
LB2  = 50;   B2s  =  0;     B2e  = -0.02;
LB3  = 40;  B3s  = -0.02;  B3e  = -0.02;
LB4  = 12.5;  B4s  = -0.02;  B4e  = +0.02;
LB5  = 10;  B5s  = +0.02;  B5e  = 0.1;

b = { LB1   {  ( B1e  - B1s )/LB1 }  ...
    ; LB2   {  ( B2e  - B2s )/LB2 }  ...
    ; LB3   {  ( B3e  - B3s )/LB3 }  ...
   %; LB31  {  ( B31e - B31s)/LB31}  ...
    ; LB4   {  ( B4e  - B4s )/LB4 }  ...
    ; LB5   {  ( B5e  - B5s )/LB5 }  ...
    };

% simple check of slope data
bsum = 0;
for ii = 1:size(b,1)
    len = b{ii,1};
    if len < 0 || ~isequal(rem(len,uinc), 0)            % todo: bound should be greater 0, ask => jorauh
        warning('CRG:checkWarning', [ num2str(ii) '. banking length = ' num2str(len) ' is negative and/or mismatch with increment of u. => fatal']);
        err_cnt = err_cnt + 1;
    end
    bsum = bsum + len;
    % maybe a check greater than (uend-ubeg) is useful
end
b = [ b; { max(0,(uend-ubeg)-bsum) {0} } ];    % if required keep last value up to the end
txtnum = txtnum + 1; data.ct{txtnum} = '... banking added';


if ~isequal(uend-ubeg, csum, ssum, bsum)
    warning('CRG:checkWarning',  'Mismatch between the length of parameter descriptions.');
    warning('CRG:checkWarning', ['range of u-coordinate : ' num2str(uend-ubeg,'%.10g')]);
    warning('CRG:checkWarning', ['range of    curvature : ' num2str(csum,'%.10g')]);
    warning('CRG:checkWarning', ['range of        slope : ' num2str(ssum,'%.10g')]);
    warning('CRG:checkWarning', ['range of      banking : ' num2str(bsum,'%.10g')]);
    warn_cnt = warn_cnt + 1;
end

% generate the road
data = crg_gen_csb2crg0(inc, u, v, c, s, b);

% show the data
txtnum = txtnum + 1; data.ct{txtnum} = '... finished';
crg_write(crg_single(data), 'crg_test_road.crg');

% show the data
data = crg_show_all(data);