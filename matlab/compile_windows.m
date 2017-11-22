function [] = compile_windows()

   SRC_DIR        = '../src/';
   MEX_DIR        = '../mex/';
   COMPILER_FLAGS = 'COMPFLAGS="/openmp /O2 $COMPFLAGS$"';
    
   src_files = fullfile(SRC_DIR, {'peakDetector_mex.cpp', 'mexutils.cpp'});   
                           
   mex_args = {'-v', '-I"..\include"', src_files{:}, COMPILER_FLAGS, '-outdir', MEX_DIR};
      
   mex(mex_args{:});
                       
end


