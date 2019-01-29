clear all;
close all
% display results
% dispRes = 0;
% 
% % build minimum crg-struct
% uinc = 0.005;
% vinc = 0.005;
% 
% nv = 201;
% nu = 10*nv;
% 
% v = -(nv-1)/2*vinc:vinc:(nv-1)/2*vinc;
% 
% z = 0.01*peaks(nv);
% z = repmat(z, nu/nv, 1);

%% Demo1: crg defined by z matrix and scalar u and v specs

% data.u = (nu-1)*uinc;
% data.v = (nv-1)*vinc/2;
% 
% np = nu-1;
% for i=1:1:np
%     if i < 201
%         data.p(i) = 0;
%     elseif i > np-200
%         data.p(i)=0;
%     else
%         for j=1:1:np-401
%             data.p(i) = 0.5*cos(j/np*1.5*pi);
%         end
%     end
% end

% for i=1:np
%     data.p(i) = 0.5*cos(i/np*1.5*pi);
% end
% 
% data.z = z;
% data.ct{1} = 'CRG defined by z matrix';
% crg_write(crg_single(data), 'demo1.crg');
% 
% dat = crg_read('demo1.crg');
% if dispRes, crg_show(dat); end

%% Demo2: General road with crg_gen_csb2crg0
uinc=0.005;
vinc=0.005;

inc=[uinc,vinc];
nv = 0.5;
nu = 10;

v = -(nv-1)/2*vinc:vinc:(nv-1)/2*vinc;

np = nu-1;
for i=1:1:np
    if i < 201
        p(i) = 0;
    elseif i > np-200
        p(i)=0;
    else
        for j=1:1:np-401
            p(i) = 0.5*cos(j/np*1.5*pi);
        end
    end
end

data.u = nu;
data.v=v;
data.z = 0.01*peaks(nv);
data.z = repmat(data.z, nu/nv, 1);

data = crg_gen_csb2crg0(inc, nu, nv);
%data = crg_gen_csb2crg0([0.005,0.005], nu, nv, c, s, b);

crg_write(crg_single(data), 'crg_gen_road.crg');
crg_show(data);

