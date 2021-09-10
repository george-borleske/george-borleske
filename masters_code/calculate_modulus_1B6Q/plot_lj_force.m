clear
close all

% Testnode is node 65
testnode = 65;
nodes    = 80;
frames   = 400;
total    = zeros(frames,1);
leg      = [];


figure;
hold on;
for j=40:50
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones Force_const %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,2))
    end
end
title(['All Lennard Jones Force const of node ', num2str(testnode)])
legend('40', '47', '48', '49', '50')
hold off

figure;
hold on;
for j=40:50
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones potential %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,3))
        if m < frames
            total = total + [A(:,3);zeros(frames - m,1)];
        else
            total = total + A(:,3);
        end
    end
end
title(['All Lennard Jones potential of node ', num2str(testnode)])
legend('40', '47', '48', '49', '50')
hold off

figure;
hold on;
for j=40:50
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones distance %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,4))
    end
end
title(['All Lennard Jones distance of node ', num2str(testnode)])
legend('40', '47', '48', '49', '50')
hold off

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure;
hold all
leg = []; 
for j=51:56
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones force_const%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,2))
    end
end
title(['All Lennard Jones force const of node ', num2str(testnode)])
legend('51', '52', '53', '54', '55', '56')
hold off

figure;
hold all
leg = []; 
for j=51:56
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones potential %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,3))
        if m < frames
            total = total + [A(:,3);zeros(frames - m,1)];
        else
            total = total + A(:,3);
        end
    end
end
title(['All Lennard Jones potential of node ', num2str(testnode)])
legend('51', '52', '53', '54', '55', '56')
hold off

figure;
hold all
leg = []; 
for j=51:56
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones distance %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,4))
    end
end
title(['All Lennard Jones distance of node ', num2str(testnode)])
legend('51', '52', '53', '54', '55', '56')
hold off

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure;
hold all
leg = []; 
for j=57:63
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones force_const %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,2))
    end
end
title(['All Lennard Jones Force const of node ', num2str(testnode)])
legend('57', '58', '59', '60', '62', '63')
hold off

figure;
hold all
leg = []; 
for j=57:63
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones potential %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,3))
        if m < frames
            total = total + [A(:,3);zeros(frames - m,1)];
        else
            total = total + A(:,3);
        end
    end
end
title(['All Lennard Jones potential of node ', num2str(testnode)])
legend('57', '58', '59', '60', '62', '63')
hold off

figure;
hold all
leg = []; 
for j=57:63
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones distance %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,4))
    end
end
title(['All Lennard Jones distance of node ', num2str(testnode)])
legend('57', '58', '59', '60', '62', '63')
hold off

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure;
hold all
leg = []; 
for j=64:70
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones force_const %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,2))
    end
end
title(['All Lennard Jones Force const of node ', num2str(testnode)])
legend('64', '67', '68', '69', '70')
hold off

figure;
hold all
leg = []; 
for j=64:70
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones potential %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,3))
        if m < frames
            total = total + [A(:,3);zeros(frames - m,1)];
        else
            total = total + A(:,3);
        end
    end
end
title(['All Lennard Jones potential of node ', num2str(testnode)])
legend('64', '67', '68', '69', '70')
hold off

figure;
hold all
leg = []; 
for j=64:70
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones distance %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,4))
    end
end
title(['All Lennard Jones distance of node ', num2str(testnode)])
legend('64', '67', '68', '69', '70')
hold off

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure;
hold all
leg = []; 
for j=71:76
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones Force_const %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,2))
    end
end
title(['All Lennard Jones Force const of node ', num2str(testnode)])
legend('71', '72', '73', '74', '75', '76')
hold off

figure;
hold all
leg = []; 
for j=71:76
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones Potential %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,3))
        if m < frames
            total = total + [A(:,3);zeros(frames - m,1)];
        else
            total = total + A(:,3);
        end
    end
end
title(['All Lennard Jones potential of node ', num2str(testnode)])
legend('71', '72', '73', '74', '75', '76')
hold off

figure;
hold all
leg = []; 
for j=71:76
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones distance %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,4))
    end
end
title(['All Lennard Jones distance of node ', num2str(testnode)])
legend('71', '72', '73', '74', '75', '76')
hold off

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure;
hold all
leg = []; 
for j=76:80
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones Force_const %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,2))
    end
end
title(['All Lennard Jones Force const of node ', num2str(testnode)])
legend('76', '77', '78', '80')
hold off

figure;
hold all
leg = []; 
for j=76:80
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones Potential %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,3))
        if m < frames
            total = total + [A(:,3);zeros(frames - m,1)];
        else
            total = total + A(:,3);
        end
    end
end
title(['All Lennard Jones potential of node ', num2str(testnode)])
legend('76', '77', '78', '80')
hold off

figure;
hold all
leg = []; 
for j=76:80
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Lennard Jones distance %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['LJ_', num2str(testnode), '_', num2str(j), '.dat'];
    if exist(Name, 'file')
        leg = [leg,j];
        A=importdata(Name);
        [m,n] = size(A);
        plot(A(:,4))
    end
end
title(['All Lennard Jones distance of node ', num2str(testnode)])
legend('76', '77', '78', '80')
hold off

figure
plot(total)
title('Total Potential energy of testnode')

x = [.5:.01:1.2];
y = 24 * 4 * (-2 * (.47^12./x.^14) + (.47^6 ./ x.^8));
figure
plot(x,y)
title('Force const as distance changes')