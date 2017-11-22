function xc = carr(x)

    dims = 1:ndims(x);
    dims = fliplr(dims);

    col = @(x) x(:);

    xc = x*1.0;
    
    xc(:) = col(permute(x,dims));
    
end