% DEFAULT SETTINGS
% clear enviroment
clear all;
close all

% build minimum crg-struct
uinc = 0.01;
vinc = 0.01;

warn_cnt = 0;
txtnum   = 0;

%% Mathod 2
ubeg = 0;
uend = 10;
u    = [ubeg uend];

lb = 1;
rb = -1;
v  = rb:vinc:lb;

%% Calculate value
inc = uinc;
nv = size(v, 2);
nu = size((ubeg:uinc:uend),2);


z = peaks(nv);
z = repmat(z, floor(nu/nv)+1, 1);

data.u = u;
data.v = v;
data.z = z;

%% curvature
% select or deselect for test purposes as shown below

LC1  = 1;  R1s  = inf;  R1e  = inf;
LC2  = 8;  R2s  = 1.5;  R2e  = 1.5;
LC3  = 2;  R3s  = 1.5;  R3e  = -1.5;

c = {% LC1   {1/R1s  ( 1/R1e  - 1/R1s )/LC1 }  ...
     ; LC2   {1/R2s  ( 1/R2e  - 1/R2s )/LC2 }  ...
%     ; LC3   {1/R3s  ( 1/R3e  - 1/R3s )/LC3 }  ...
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

LS1  = 5;   S1s  =  0.0;    S1e  =  0.0;

s = { LS1   { S1s ( S1e  - S1s )/LS1 }  ...
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

LB1  = 2;  B1s  =  0;     B1e  = 0;
LB2  = 4;   B2s  =  0;     B2e  = -0.02;
LB3  = 4;  B3s  = -0.02;  B3e  = 0.02;

b = { %LB1   { B1s ( B1e  - B1s )/LB1 }  ...
    ; LB2   { B2s ( B2e  - B2s )/LB2 }  ...
    %; LB3   { B3s ( B3e  - B3s )/LB3 }  ...
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

% generate the road
data = crg_gen_csb2crg0(inc, u, v, c, s, b);

% show the data
txtnum = txtnum + 1; data.ct{txtnum} = '... finished';
crg_write(crg_single(data), 'crg_test_road.crg');

% show the data
data = crg_show_all(data);