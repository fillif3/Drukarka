%Zdefiniowanie parametrów (pozycje kolumn, pocz¹tkowe pozycje wózka)
r=25
x1=0 %kol pierwsa
x2=0
x3=24
y1=0
y2=28
y3=14
z=0
zg=60
xc=3.9 %pozycja g³owicy
yc=14
zc=30
% pocz¹tkowa pozycja wózków
wozek1=zc+sqrt(r^2-(x1-xc)^2-(y1-yc)^2)
wozek2=zc+sqrt(r^2-(x2-xc)^2-(y2-yc)^2)
wozek3=zc+sqrt(r^2-(x3-xc)^2-(y3-yc)^2)
% rysiwanie kolumn
kol1 = line([x1,x1],[y1,y1],[z,zg])
kol2 = line([x2,x2],[y2,y2],[z,zg])
kol3 = line([x3,x3],[y3,y3],[z,zg])
% rysowanie lini wozek-g³owica
ramie1=line([x1,xc],[y1,yc],[wozek1,zc])
ramie2=line([x2,xc],[y2,yc],[wozek2,zc])
ramie3=line([x3,xc],[y3,yc],[wozek3,zc])
view(60,30)


for t=0:0.1:100
    %poruszanie siê wzd³u¿ p³asczyzny docelowo
    xc=10 + sin(t)
    yc=10 + cos(t)
    %obliczenie nowych pozycji wózka
    wozek1=zc+sqrt(r^2-(x1-xc)^2-(y1-yc)^2)
    wozek2=zc+sqrt(r^2-(x2-xc)^2-(y2-yc)^2)
    wozek3=zc+sqrt(r^2-(x3-xc)^2-(y3-yc)^2)
    %narysowanie ich
    set(ramie1,'XData',[x1,xc],'YData',[y1,yc],'ZData',[wozek1,zc])
    set(ramie2,'XData',[x2,xc],'YData',[y2,yc],'ZData',[wozek2,zc])
    set(ramie3,'XData',[x3,xc],'YData',[y3,yc],'ZData',[wozek3,zc])
    drawnow
    if (t>0) %za ka¿dym razem oprócz pierwszegoli liczymy kroki
        krok1=round(200*(wozek1-stare1)) %ile kroków
        krok2=round(200*(wozek2-stare2))
        krok3=round(200*(wozek3-stare3))
        fprintf(s,'x %d y %d z %d t %d',[krok1 krok2 krok3 150]) %wys³¹nie kroków i temperatury
        while (s.BytesAvailable == 0) %czekanie kiedy kroki siê zakoñcz¹
        end
        while (s.BytesAvailable>0)
        fscanf(s) %czytanie temperautry
        end
    end
    stare1=wozek1 %zapamiêtanie starych pozycji wózka w celu obliczenia kroków póŸniej (kroku =nowe po³oznenie - stare po³ozenie)
    stare2=wozek2
    stare3=wozek3
end
