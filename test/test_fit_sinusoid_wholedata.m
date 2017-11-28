
%% Generate cancellation signal
N  = size(twixobj.data, 1);
tt = (0:N-1)*0.5;
dt = 0.5
fnyq = 0.5/dt;
ff = getfreqaxis(tt);
df = 1.0/(0.5*N);

tt = tt(:);
ff = ff;

signal = @(f0) exp(1j*2*pi*bsxfun(@times,f0,tt))/sqrt(N);

beta = 0.5;
fmin = ff(380);
fmax = ff(end);

kdata  = twixobj.data(:,:,1:(38*1000));

f0_vec   = peakDetector(squeeze(kdata(:,1,:)), fmin, fmax, 1.0e-6);
f0_vec = reshape(f0_vec, 1, 1, []);


%% Solve for constant
p = signal(f0_vec);

z     = sum(bsxfun(@times, conj(p), kdata),1);
ptsig = bsxfun(@times, z, p);

coil_signals = squeeze(z);



%z = dot(p,y)
                                            
%% plots


