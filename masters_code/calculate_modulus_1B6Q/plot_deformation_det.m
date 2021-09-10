close all
clear

testnode = 28;

Name = ['node', num2str(testnode), '_F_det.txt'];
if exist(Name, 'file')
    A = importdata(Name);
    figure;
    plot(A);
    title('Deformation matrix determinant of testnode')
    
else
    disp('cant open file')
end