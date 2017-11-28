%% compile mex file
%compile;

%% run program

%crand = @(varargin) complex( rand( varargin{:} ), rand( varargin{:} ) );


N     = size(x,2);
fmin  = 0.6;
fmax  = 1.0;

fmin  = repmat(fmin, [N,1]);
fmax  = repmat(fmax, [N,1]);

fprintf('\n\nRunning mex program ... \n\n\n');

tic;
fout = peakDetector(x, 'fmin', fmin, 'fmax', fmax);
toc;
