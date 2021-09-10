clear
clc
close all
nodes = 120;

% Node 35 bad shear mod
ls_size     = 20;
start       = 10; 
last        = 300;
first_alpha = 7;          % add 1 since first node in alpha helix is fixed
last_alpha  = 32;
xx2         = start:last;         % frames for stress and strain
xx          = start+ls_size:last; % frames of interest for compliance matrix, young's modulus, and engineering constants
[~, mx2]    = size(xx2);
[~, mx]     = size(xx);
yy          = start+1:last-ls_size+1;
temp        = [];



for i = first_alpha:last_alpha
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Engineering Constants for isotropic material %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['node', num2str(i), '_trans_elas.txt'];
    if exist(Name, 'file')
        A=importdata(Name);
        [m,n] = size(A);
        
        EM11   = median(A(yy,2));
        EM12   = median(A(yy,3));
        EM13   = median(A(yy,4));
        EM33   = median(A(yy,5));
        EM44   = median(A(yy,6));
        EM66   = median(A(yy,7));
        
        eng = ones(6,m);
        eng(1,:) = eng(1,:) * EM11;
        eng(2,:) = eng(2,:) * EM12;
        eng(3,:) = eng(3,:) * EM13;
        eng(4,:) = eng(4,:) * EM33;
        eng(5,:) = eng(5,:) * EM44;
        eng(6,:) = eng(6,:) * EM66;
        
        i
        temp = [temp; '            ', num2str(i,'%02d'), ' & ', num2str(EM11,'%+9.4e'), ' & ', num2str(EM12,'%+9.4e'), ' & ', num2str(EM13,'%+9.4e'), ...
            ' & ', num2str(EM33,'%+9.4e'), ' & ', num2str(EM44,'%+9.4e'), ' & ', num2str(EM66,'%+9.4e'), ' \\ \hline'];
        
        figure;
        subplot(2,3,1);
        plot(xx,A(yy,2),xx,eng(1,yy))
        title(['Elastic Modulus, C_1_1 Node ', num2str(i)])
        
        subplot(2,3,2);
        plot(xx,A(yy,3),xx,eng(2,yy))
        title('C_1_2')
        
        subplot(2,3,3);
        plot(xx,A(yy,4),xx,eng(3,yy))
        title('C_1_3')
        
        subplot(2,3,4);
        plot(xx,A(yy,5),xx,eng(4,yy))
        title('C_3_3')
        
        subplot(2,3,5);
        plot(xx,A(yy,6),xx,eng(5,yy))
        title('C_4_4')
        
        subplot(2,3,6);
        plot(xx,A(yy,7),xx,eng(6,yy))
        title('C_6_6')
    end
end

temp

