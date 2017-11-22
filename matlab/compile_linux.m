function [] = compile_linux()

   SRC_DIR        = '../src/';
   MEX_DIR        = '../mex/';
   COMPILER_FLAGS = {'CXXFLAGS="$CXXFLAGS -w -fopenmp"', 'LDFLAGS="$LD_FLAGS -fopenmp -lgomp"', 'COP/TIMFLAGS=-O3'};
    
   src_files = fullfile(SRC_DIR, {'peakDetector_mex.cpp', 'mexutils.cpp'});   
                           
   mex_args = {'-v', '-outdir', MEX_DIR, '-I"../include"', COMPILER_FLAGS{:}, src_files{:}};
      
   mex(mex_args{:});
                       
end

