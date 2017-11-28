function argChecker = getArgChecker(args)

    % args is either a cell array with name-value pairs or a struct
    % specifying parameters. 
    %
    % Example:
    %
    % args = {'width', 10, 'height', 5}
    %
    % argChecker = getArgChecker(args);
    %
    % Now arguments can be checked according to the following template
    % someVariable = argChecker('someVariable', defaultValue)
    % If no value is specified it gets the default value.
    %
    % width  = argChecker('width', 7);
    % height = argChecker('height', 3);
    % length = argChecker('length', 13);
    %
    % This results in width getting a value of 10, height getting a value
    % of 5, and length getting a value of 13. 

    if isstruct(args)
        args = struct2argcell(args);
    end
    
    argChecker = @(argName, defaultValue) checkArg(args, argName, defaultValue);

end

function val = checkArg(args, argName, defaultValue)

    for i = 1:numel(args)
        if strcmp(args{i}, argName) && (i<numel(args))
            val = args{i+1};
            return;
        end
    end
    
    val = defaultValue;

end

function argCell = struct2argcell(S)

    argCell = {};
    
    allFields = fields(S);
    for i = 1:numel(allFields)
        f = allFields{i};
        argCell = cat(2,argCell,f,S.(f));        
    end


end