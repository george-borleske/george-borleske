clear
close all

% Testnode is node 65
testnode = 65;
nodes    = 80;
frames   = 400;
total    = zeros(frames,1);

for j = 1:nodes
    Name = ['LJ_stress_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        A=importdata(Name);
        [m,n] = size(A);
        if m > 10
%             figure
%             plot(A(:,2))
%             titl = ['Force Const between nodes ', num2str(testnode), ' and ', num2str(j)]
%             title(titl)
            figure
            plot(A(:,3))
            titl = ['Stress energy (F*r) x component between nodes ', num2str(testnode), ' and ', num2str(j)];
            title(titl)
            
            if m < frames
                total = total + [A(:,3);zeros(frames - m,1)];
            else
                total = total + A(:,3);
            end
        end
    end
end

figure
plot(total)
title('Total x-component stress from largest contributers')