[m,n] = size(mat);
[k,~] = size(b);

% mat in code is separated into three parts 
eq1 = mat(1:20,:);
eq2 = mat(21:40,:);
eq3 = mat(41:60,:);

% b in code is separated into three parts
beq1 = b(1:20);
beq2 = b(21:40);
beq3 = b(41:60);

aug1 = [eq1' * eq1, eq1' * beq1];
aug2 = [eq2' * eq2, eq2' * beq2];
aug3 = [eq3' * eq3, eq3' * beq3];

sol1 = rref(aug1);
sol2 = rref(aug2);
sol3 = rref(aug3);

young1 = 1 / sol1(1,3)
young2 = 1 / sol2(1,3)
young3 = 1 / sol3(1,3)