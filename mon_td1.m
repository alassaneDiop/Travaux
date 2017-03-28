% % EXERCICE 3
% 
% % randi genere aleatoirement des valeurs
% V1 = randi(25, 1, 100) % randi génére 100 valeurs aléatoires entre 1 et 25
% V2 = randi(25, 1, 100)
% 
% % Avec la fonction max
% % max compare les deux tableaux en prenant les elements maximaux
% V3 = max(V1, V2)
% 
% % sans la fonction max
% % T est un tableau de booléen résultant de la comparaison des valeurs de V1 et V2
% T = V1 > V2
% % si T est vrai on prend V1, si T est faux on prend V2
% V4 = V1 .* T + V2.* ~T


% % EXERCICE 4
% 
% % randi genere les nombres entres 1 et 10 de maniére aléatoire et crée un
% % tableau de 3X3
% A = randi([1 10], 3, 3)
% A = A - mod(A, 2)
% % mod est le modulo de A[i] et 2
% 
% B = randi([1 10], 3, 3)
% B = B + ~mod(B, 2)
% % ~ signifie la négation !
% 
% coeffImpair = [1:2:6] % coeffImpair contient les nombres de 1 à 12 par saut de 2
% coeffPair = [2:2:6] % coeffPair contient les nombres de 2 à 12 par saut de 2
% C(coeffImpair, :) = A(:,:)
% C(coeffPair, :) = B(:,:)


% EXERCICE 5

% X = -10:0.1:10
% Y = normpdf(X,0,1)
X = 1
Y = normpdf(X, 10)


function y = droite2DVD(x, vd, p)
vd = [1 2]
p = [1 1]
if(vd(1) == 0)
    y = p(1)
else
    y = vd(2)/vd(1)(x - p(1)) + p(2)
    
plot(x,y)
    
    