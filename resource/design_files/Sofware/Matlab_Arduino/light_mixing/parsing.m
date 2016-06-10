function [] = parsing(file,leds, rgb)
%   input: strings from serial input
%   output: none
%   function writes to an xlsx file, recording all measurements.
disp('Inside parsing function');
disp(leds);
disp(rgb);

row = zeros(1,6+4);
keys = ['r';'g';'b';'a';'p';'w';'c'];
for n = 1:6
    Key   = strcat(keys(n),'=');
    Index = strfind(leds, Key);
    Value = sscanf(leds(Index() + length(Key):end), '%g', 1);
    row(n) = Value;
end
for n = 7:10
    a = mod(n,8);
    if a < 7
        a = a + 1;
    end
    Key   = strcat(keys(a),'=');
    Index = strfind(rgb, Key);
    Value = sscanf(rgb(Index() + length(Key):end), '%g', 1);
    row(n) = Value;
end
a=xlsread(file); %if it's a cvs file, cvsread and cvswrite, see matlab help for more
nRows = size(a,1);
b = [a;row];
xlswrite(file, b); 

end

