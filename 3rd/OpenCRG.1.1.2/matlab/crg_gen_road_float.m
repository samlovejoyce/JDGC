
clear all;
close all;

data = ipl_read('crg_test_gen_road.crg');

data = ipl_write(data, 'crg_test_gen_road_float.crg', 'LRFI');

crg = crg_read('crg_test_gen_road_float.crg');
crg_show(crg);
