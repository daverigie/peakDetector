function [ptsig, coil_signals] = fitPilotTone(kdata, channelIdx, varargin)

    if nargin < 2
        channelIdx = determineStrongestPTChannel(kdata);
    end

    %% Generate cancellation signal
    N  = size(kdata, 1);
    tt = (0:N-1)*0.5;
    dt = 0.5

    tt = tt(:);

    signal = @(f0) exp(1j*2*pi*bsxfun(@times,f0,tt))/sqrt(N);

    tstart = tic;
    fprintf('\nRunning PT fitting mex function...');
    f0_vec   = peakDetector(squeeze(kdata(:,channelIdx,:)), varargin{:});
    f0_vec = reshape(f0_vec, 1, 1, []);
    fprintf('\nDone in %f seconds.\n\n', toc(tstart));


    %% Solve for constant
    p = signal(f0_vec);
    z     = sum(bsxfun(@times, conj(p), kdata),1);
    ptsig = bsxfun(@times, z, p);

    coil_signals = squeeze(z);

                                            
end

function idx = determineStrongestPTChannel(kdata)


    numChannels = size(kdata,2);
    
    for i = 1:numChannels
       kurt_vals(i) = kurtosis(kdata(:,i,1)); 
    end
    
    [~,idx] = max(kurt_vals);
    
    fprintf('\nPilot tone is strongest in channel %i', idx);
    fprintf('\n\n');


end