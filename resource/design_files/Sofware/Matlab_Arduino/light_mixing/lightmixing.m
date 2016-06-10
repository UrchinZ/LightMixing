%lightmixing.m
%test.m
%Zhaoyi Zhang last edit 05/26/2016
%instrfind to check port availability
s = serial('COM5','Baudrate',9600);
file = 'calibration_data1.xlsx';
fopen(s);
pause(2);

%sythetic: after command, wait for response.
try
    %=======================Edit Only After This Line ===================
    %Commands
    check = fscanf(s);
    fprintf(s,'test');
    disp(fscanf(s));
    pause(2);
    fprintf(s,'set red=50');
    disp(fscanf(s));
    disp(fscanf(s));
    fprintf(s,'set green=90');
    disp(fscanf(s));
    fprintf(s,'set blue=70');
    pause(1);
    disp(fscanf(s));
    fprintf(s,'set purple=70');
    disp(fscanf(s));
    fprintf(s,'set white=20');
    disp(fscanf(s));
    fprintf(s,'set amber=20');
    disp(fscanf(s));
    fprintf(s,'getLED');
    disp(fscanf(s));
    fprintf(s,'rand');
    leds = fscanf(s);
    disp(leds);
    fprintf(s,'getsensor');
    rgb = fscanf(s);
    disp(rgb);
    parsing(file,leds,rgb);
    %=========================Edit Only Above This Line ===================
catch err
end
fclose(s);