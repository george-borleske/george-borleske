clear
close all

ls_size     = 20;
start       = 10; 
last        = 399;
first_alpha = 12; 
last_alpha  = 73;
xx2         = start:last;         % frames for stress and strain
xx          = start+ls_size:last; % frames of interest for compliance matrix, young's modulus, and engineering constants
[~, mx2]    = size(xx2);
[~, mx]     = size(xx);
yy          = start+1:last-ls_size+1;
temp_y      = [];
temp_p      = [];
temp_s      = [];
temp_avg    = [];



for i = first_alpha:last_alpha
    i
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Stress %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['node', num2str(i), '_stress_cau.txt'];
    if exist(Name, 'file')
        
        A=importdata(Name);
        [m,n] = size(A);
        
        % linear regression for xx component of stress
        lin_reg_str = zeros(6,mx2);
        for j = 1:6
            coef_str =  [ones(mx2,1) xx2'] \ A(xx2,j+1);
            lin_reg_str(j,:) = coef_str(1) + coef_str(2) * xx2;
        end
        
        figure;
        subplot(2,3,1);
        plot(xx2,A(xx2,2),xx2,lin_reg_str(1,:))
        title(['XX Stress, Node ', num2str(i)])
        legend('every frame', 'linear regression')
        
        subplot(2,3,2);
        plot(xx2,A(xx2,3),xx2,lin_reg_str(2,:))
        title('YY')
        
        subplot(2,3,3);
        plot(xx2,A(xx2,4),xx2,lin_reg_str(3,:))
        title('ZZ')
        
        subplot(2,3,4);
        plot(xx2,A(xx2,5),xx2,lin_reg_str(4,:))
        title('ZX')
        
        subplot(2,3,5);
        plot(xx2,A(xx2,6),xx2,lin_reg_str(5,:))
        title('ZY')
        
        subplot(2,3,6);
        plot(xx2,A(xx2,7),xx2,lin_reg_str(6,:))
        title('XY')
        B = A;
        
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % Strain %
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        Name = ['node', num2str(i), '_strain.txt'];
        
        A=importdata(Name);
        [m,n] = size(A);
        
        % linear regression for xx component of stress
        lin_reg_def = zeros(6,mx2);
        for j = 1:6
            coef_str =  [ones(mx2,1) xx2'] \ A(xx2,j+1);
            lin_reg_def(j,:) = coef_str(1) + coef_str(2) * xx2;
        end
        
        figure;
        subplot(2,3,1);
        plot(xx2,A(xx2,2),xx2,lin_reg_def(1,:))
        title(['XX Strain, Node ', num2str(i)])
        legend('every frame', 'linear regression')
        
        subplot(2,3,2);
        plot(xx2,A(xx2,3),xx2,lin_reg_def(2,:))
        title('YY')
        
        subplot(2,3,3);
        plot(xx2,A(xx2,4),xx2,lin_reg_def(3,:))
        title('ZZ')
        
        subplot(2,3,4);
        plot(xx2,A(xx2,5),xx2,lin_reg_def(4,:))
        title('ZX')
        
        subplot(2,3,5);
        plot(xx2,A(xx2,6),xx2,lin_reg_def(5,:))
        title('ZY')
        
        subplot(2,3,6);
        plot(xx2,A(xx2,7),xx2,lin_reg_def(6,:))
        title('XY')
        
        % Equation 1.2.44 in Elasticity of Transveresely Isotropic Materials
        % a = 1 / E, b = v / E
        % [stress[0], -stress[1] - stress[1], strain[0];
        %  stress[1], -stress[2] - stress[0], strain[1];
        %  stress[2], -stress[0] - stress[1], strain[2]]
%         mat = [lin_reg_str(1,1), -lin_reg_str(1,2) - lin_reg_str(1,3), lin_reg_def(1,1);
%             lin_reg_str(1,2), -lin_reg_str(1,3) - lin_reg_str(1,1), lin_reg_def(1,2);
%             lin_reg_str(1,3), -lin_reg_str(1,1) - lin_reg_str(1,2), lin_reg_def(1,3)];
        
        
        mat1 = [lin_reg_str(1,1), -lin_reg_str(2,1) - lin_reg_str(3,1), lin_reg_def(1,1);
            lin_reg_str(1,100), -lin_reg_str(2,100) - lin_reg_str(3,100), lin_reg_def(1,100)];
        
        mat2 = [lin_reg_str(2,1), -lin_reg_str(3,1) - lin_reg_str(1,1), lin_reg_def(2,1);
            lin_reg_str(2,100), -lin_reg_str(3,100) - lin_reg_str(1,100), lin_reg_def(2,100)];
        
        mat3 = [lin_reg_str(3,1), -lin_reg_str(1,1) - lin_reg_str(2,1), lin_reg_def(3,1);
            lin_reg_str(3,100), -lin_reg_str(1,100) - lin_reg_str(2,100), lin_reg_def(3,100)];
        
        rowr1    = rref(mat1);                  % row reduced matrix
        rowr2    = rref(mat2);
        rowr3    = rref(mat3);
        
        young1   = 1 / rowr1(1,3);
        poisson1 = rowr1(2,3) / rowr1(1,3);
        shear1   = young1 / (2 + 2 * poisson1);  % G = E/(2+2v)i
        
        young2   = 1 / rowr2(1,3);
        poisson2 = rowr2(2,3) / rowr2(1,3);
        shear2   = young2 / (2 + 2 * poisson2);  % G = E/(2+2v)i
        
        young3   = 1 / rowr3(1,3);
        poisson3 = rowr3(2,3) / rowr3(1,3);
        shear3   = young3 / (2 + 2 * poisson3);  % G = E/(2+2v)i
        
        young_avg = (young1 + young2 + young3) / 3;
        poisson_avg = (poisson1 + poisson2 + poisson3) / 3;
        shear_avg = (shear1 + shear2 + shear3) / 3;
        
        
        temp_y = [temp_y; '   ', num2str(i,'%02d'), '  ', num2str(young1,'%+9.4e'), '  ', num2str(young2,'%+9.4e'), '  ', num2str(young3,'%+9.4e'), '  ', num2str(young_avg,'%+9.4e')];
        temp_p = [temp_p; '   ', num2str(i,'%02d'), '  ', num2str(poisson1,'%+9.4e'), '  ', num2str(poisson2,'%+9.4e'), '  ', num2str(poisson3,'%+9.4e'), '  ', num2str(poisson_avg,'%+9.4e')];
        temp_s = [temp_s; '   ', num2str(i,'%02d'), '  ', num2str(shear1,'%+9.4e'), '  ', num2str(shear2,'%+9.4e'), '  ', num2str(shear3,'%+9.4e'), '  ', num2str(shear_avg,'%+9.4e')];
        
        temp_avg = [temp_avg; '   ', num2str(i,'%02d'), ' & ', num2str(young_avg,'%+9.4e'), ' & ', num2str(poisson_avg,'%+9.4e'), ' & ', num2str(shear_avg,'%+9.4e'), ' \\ \hline'];
        %prompt = 'Hit enter to continue ';
        %pointless = input(prompt);
    end
end


temp_y
temp_p
temp_s
temp_avg
