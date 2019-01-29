%% STEP 1: create longitudinal and lateral profile(s) like this
% u ----> coordinate begin middle sections end
% v ----> coordinate left origin right
% l ---> left hand side
% r ---> right hand side
% w ---> width of whole road
% c ---> center of road
% p --> profile
% r --> raughness
% _ -> name_sect
% _ -> name_prof
% offset or amplitude to origin
% |
ubeg=0;
uend=100;
uwp_road_sect = [ ubeg uend ]; % road width u sections
uwp_road_prof = [ 1 1 ];
vwp_road_sect = 0 + [ 3 : -0.5 : -3 ]; % road width v sect
vwp_road_prof = 1 * [ ones(size(vwp_road_sect)) ];
ulp_lane_sect = [ ubeg uend ]; % left lane u sections
ulp_lane_prof = [ 1 1 ];
vlp_lane_sect = 1.25 + [ 1 : -0.2 : -1 ]; % left lane v sect
vlp_lane_prof = 1 * [ 1 0.8 0.8 0.6 0.6 0.6 0.6 0.6 0.8 0.8 1 ];
ulr_lane_sect = 100 + [ 0 10 50 60 ]; % left lane u sections
ulr_lane_prof = [ 1 0.8 0.8 1 ];
vlr_lane_sect = 1.25 + [ 1 : -0.2 : -1 ]; % left lane v sect
vlr_lane_prof = 1 * [ ones(size(vlr_lane_sect)) ];
urp_lane_sect = [ ubeg 30 40 50 80 90 uend ]; % right lane u sections
urp_lane_prof = [ 1 1 0.6 0.8 0.5 1 1 ];
vrp_lane_sect = -1.25 + [ 1 -1 ]; % right lane v sect
vrp_lane_prof = 1 * [ 1 1 ];
% mode one of {'Profile' 'Random' 'Ignore' }
% | u section u profile v section v profile valid only for random profile(s)
% | | | | | /----------^----------\
uv_mue = { ...
; { 'Profile' [ uwp_road_sect ; uwp_road_prof ] [ vwp_road_sect ; vwp_road_prof ] } ...
; { 'Random' [ ulr_lane_sect ; ulr_lane_prof ] [ vlr_lane_sect ; vlr_lane_prof ] 2010 0.5 1 0.4 0.4 } ...
; { 'Profile' [ ulp_lane_sect ; ulp_lane_prof ] [ vlp_lane_sect ; vlp_lane_prof ] } ...
; { 'Profile' [ urp_lane_sect ; urp_lane_prof ] [ vrp_lane_sect ; vrp_lane_prof ] } ...
};
% ^ ^ ^ ^ ^
% | | | | |
% | | | | v_smooth (random) in range 0..1
% | | | u_smooth (random) in range 0..1
% | | max amplithude random
% | min amplithude random
% initialize state of random generator
%% end of user settings
%% STEP 2: create and check lateral profile vector
v = crg_check_uv_descript(uv_mue, {'Ignore' 'Profile' 'Random'});