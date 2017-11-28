function fout = testmex_wrapper(kdata, varargin)

    %%%%%%%%%%%%%%%%%%%%%%%%%% CHECK INPUTS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    argchecker = getArgChecker(varargin); % Set Default Arguments
    fmin       = argchecker('fmin', 0.0);
    fmax       = argchecker('fmax', 1.0);
    ftol       = argchecker('ftol', 1.0e-9);
    
    fmin = double(fmin(:));
    fmax = double(fmax(:));
    
    kdata = double(complex(kdata));
    
    if numel(fmin) == 1
        fmin = repmat(fmin, [size(kdata,2), 1]);
    end
    
    if numel(fmax) == 1
        fmax = repmat(fmax, [size(kdata,2), 1]);
    end
    
    if ~checkdims(kdata, fmin, fmax)
        error('Problem with input data. Is it oriented wrong?');
    end
        
    ftol = double(ftol);
    
    %%%%%%%%%%%%%%%%%%%%% CALL MEX FUNCTION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
       
    fout = peakDetector_mex(kdata, fmin, fmax, ftol);


end

function tf = checkdims(kdata, fmin, fmax)

    tf = true;
    
    [numSamples, numLines] = size(kdata);
    
    if ~isequal(size(fmin), [numLines, 1])
        tf = false;
    end
        
    if ~isequal(size(fmax), [numLines, 1])
        tf = false;
    end
        
end