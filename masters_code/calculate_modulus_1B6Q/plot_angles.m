close all
clear
testnode = 28;
eq_ang   = 96;   % equilibrium angle in degrees
eq_ang   = cos(eq_ang * pi / 180);

Name = ['Angle_of_testnode_', num2str(testnode), '.txt'];
if exist(Name, 'file');
    A = importdata(Name);
    [m,n] = size(A);
    figure;
    xx = 0:1:m-1;
    B = ones(m,1) * eq_ang;
    plot(xx,A(:,5),xx,A(:,9),xx,A(:,13),xx,B(:,1));
    legend('26, 27, 28', '27, 28, 29', '28, 29, 30', 'Equilibrium angle 96 degrees')
    title(['Cosine of the angles of angular bonds including the testnode ', num2str(testnode)]) 
    
end