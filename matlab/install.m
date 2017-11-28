clear mex;

if ispc
    compile_windows;
else
    compile_linux;
end

cd ..

addpath(pwd);
addpath(genpath(fullfile(pwd,'mex')));