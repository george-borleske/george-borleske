clear
close all

% Testnode is node 91
i = 28;
%before_testnode = 87;
%after_testnode  = 93;
ls_size = 20;
start = 1;
last  = 399;
xx = start:last; % frames of interest
yy = start-ls_size+1:last-ls_size+1;




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Position of testnode %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Position_node_', num2str(i), '.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A);
    %xx = [1:m];
    figure;
    plot(xx,A(xx,2),'b',xx,A(xx,3),'k',xx,A(xx,4),'r')
    legend('x coordinate', 'y coordinate', 'z coordinate')
    title('position of testnode')
end
C = A;

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % Position of nodes bonded to testnode %
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Name = ['Position_node_', num2str(before_testnode), '.txt'];
% if exist(Name, 'file')
%     
%     A=importdata(Name);
%     [m,n] = size(A);
%     %xx = [1:m];
%     figure;
%     plot(xx,A(xx,2),'b',xx,A(xx,3),'k',xx,A(xx,4),'r')
%     legend('x coordinate', 'y coordinate', 'z coordinate')
%     title('position of node 87')
% end
% Name = ['Position_node_', num2str(after_testnode), '.txt'];
% B = A;
% if exist(Name, 'file')
%     
%     A=importdata(Name);
%     [m,n] = size(A);
%     %xx = [1:m];
%     figure;
%     plot(xx,A(xx,2),'b',xx,A(xx,3),'k',xx,A(xx,4),'r')
%     legend('x coordinate', 'y coordinate', 'z coordinate')
%     title('position of node 93')
% end
% % plot bond lengths of each bond
% figure;
% plot(xx,C(xx,2)-B(xx,2),'b',xx,C(xx,3)-B(xx,3),'k',xx,C(xx,4)-B(xx,4),'r')
% legend('x coordinate', 'y coordinate', 'z coordinate')
% title('bond length between nodes 91 and 87')
% figure;
% plot(xx,A(xx,2)-C(xx,2),'b',xx,A(xx,3)-C(xx,3),'k',xx,A(xx,4)-C(xx,4),'r')
% legend('x coordinate', 'y coordinate', 'z coordinate')
% title('bond length between nodes 91 and 93')
% figure;
% plot(xx,A(xx,2)-B(xx,2),'b',xx,A(xx,3)-B(xx,3),'k',xx,A(xx,4)-B(xx,4),'r')
% legend('x coordinate', 'y coordinate', 'z coordinate')
% title('bond length between nodes 87 and 93')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Bond Energy %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Energy_after_bond_', num2str(i), '.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A);
    
    figure;
    subplot(1,3,1);
    plot(xx,A(xx,2))
    title('XX Bond Energy')
    
    subplot(1,3,2);
    plot(xx,A(xx,3))
    title('YY  F x r')
    
    subplot(1,3,3);
    plot(xx,A(xx,4))
    title('ZZ')
    %axis equal
        
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Angle Energy %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Energy_after_angle_', num2str(i), '.txt'];
if exist(Name, 'file')
    
    B=importdata(Name);
    C = B - A;                    % subtract bond energy from current total energy to get angle energy
    [m,n] = size(B);
    
    figure
    subplot(1,3,1);
    plot(xx,C(xx,2))
    title('XX Angle Energy')
    
    subplot(1,3,2);
    plot(xx,C(xx,3))
    title('YY')
    
    subplot(1,3,3);
    plot(xx,C(xx,4))
    title('ZZ')
        
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
    
    A = B;  % Set A to the current total energy (bond and angle only)
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Dihedral Energy %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Energy_after_dihedral_', num2str(i), '.txt'];
if exist(Name, 'file')
    
    B=importdata(Name);
    C = B - A;                    % subtract previous energy from current total energy to get dihedral energy
    [m,n] = size(B);
    
    figure;
    subplot(1,3,1);
    plot(xx,C(xx,2))
    title('XX Dihedral Energy')
    
    subplot(1,3,2);
    plot(xx,C(xx,3))
    title('YY')
    
    subplot(1,3,3);
    plot(xx,C(xx,4))
    title('ZZ')
        
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
    
    A = B;  % Set A to the current total energy (bond, angle, and dihedral only)
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Coulomb Energy %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Energy_after_Coulomb_', num2str(i), '.txt'];
if exist(Name, 'file')
    
    B=importdata(Name);
    C = B - A;                    % subtract previous energy from current total energy to get Coulomb energy
    [m,n] = size(B);
    
    figure;
    subplot(1,3,1);
    plot(xx,C(xx,2))
    title('XX Coulomb Energy')
    
    subplot(1,3,2);
    plot(xx,C(xx,3))
    title('YY')
    
    subplot(1,3,3);
    plot(xx,C(xx,4))
    title('ZZ')
        
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
    
    A = B;  % Set A to the current total energy (bond, angle, dihedral, Coulomb)
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Lennard Jones Energy %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Energy_after_LJ_', num2str(i), '.txt'];
if exist(Name, 'file')
    
    B=importdata(Name);
    C = B - A;                       % subtract previous energy from current total energy to get Lennard Jones energy
    [m,n] = size(B);
    
    figure;
    subplot(1,3,1);
    plot(xx,C(xx,2))
    title('XX Lennard Jones Energy')
    
    subplot(1,3,2);
    plot(xx,C(xx,3))
    title('YY')
    
    subplot(1,3,3);
    plot(xx,C(xx,4))
    title('ZZ')
        
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
    
    A = B;  % Set A to the current total energy (includes all energies)
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Total Energy %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Energy_after_bond_', num2str(i), '.txt'];
if exist(Name, 'file')
 
    [m,n] = size(A);
    sample_total_en = zeros(14,n); % averaging stress of 99 frames
    
    figure;
    subplot(1,3,1);
    plot(xx,A(xx,2))
    title('XX Total Energy')
    
    subplot(1,3,2);
    plot(xx,A(xx,3))
    title('YY')
    
    subplot(1,3,3);
    plot(xx,A(xx,4))
    title('ZZ')
        
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
end


xx2     = start:last;         % frames for stress and strain
xx      = start+ls_size:last; % frames of interest for compliance matrix,
                              % young's modulus, and engineering constants
[~, mx2] = size(xx2);
[~, mx] = size(xx);
yy      = start+1:last-ls_size+1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stress %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_stress.txt'];
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
    title('XX 1st Piola Kirchoff Stress')
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
    
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
end



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
    title('XX Cauchy Stress')
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
    
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Strain %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_strain.txt'];
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
    title('XX Strain')
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
    
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Deformation tensor %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_strain_comp.txt'];
if exist(Name, 'file')
    A=importdata(Name);
    [m,n] = size(A);
    
    figure;
    subplot(3,3,1);
    plot(A(:,1))
    title('xx Deformation tensor')
    
    subplot(3,3,2);
    plot(A(:,2))
    title('xy')
    
    subplot(3,3,3);
    plot(A(:,3))
    title('xz')
    
    subplot(3,3,4);
    plot(A(:,4))
    title('yx')
    
    subplot(3,3,5);
    plot(A(:,5))
    title('yy')
    
    subplot(3,3,6);
    plot(A(:,6))
    title('yz')
    
    subplot(3,3,7);
    plot(A(:,7))
    title('zx')
    
    subplot(3,3,8);
    plot(A(:,8))
    title('zy')
    
    subplot(3,3,9);
    plot(A(:,9))
    title('zz')
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Deformation tensor determinant %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_F_det.txt'];
if exist(Name, 'file')
    A=importdata(Name);
    [m,n] = size(A);
    
    figure;
    plot(A);
    title('Determinant of Deformation tensor')
end