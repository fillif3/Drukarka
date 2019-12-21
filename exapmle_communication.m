%Example of communication (with visualzation)
r=25
x1=0 %kol first
x2=0
x3=24
y1=0
y2=28
y3=14
z=0
zg=60
xc=3.9 %head's position
yc=14 %head's position
zc=30 %head's position

wozek1=zc+sqrt(r^2-(x1-xc)^2-(y1-yc)^2) %compute position with inverse kinematics
wozek2=zc+sqrt(r^2-(x2-xc)^2-(y2-yc)^2) %compute position with inverse kinematics
wozek3=zc+sqrt(r^2-(x3-xc)^2-(y3-yc)^2) %compute position with inverse kinematics
%colums
kol1 = line([x1,x1],[y1,y1],[z,zg]) 
kol2 = line([x2,x2],[y2,y2],[z,zg])
kol3 = line([x3,x3],[y3,y3],[z,zg])
% lines from columns to motors
ramie1=line([x1,xc],[y1,yc],[wozek1,zc])
ramie2=line([x2,xc],[y2,yc],[wozek2,zc])
ramie3=line([x3,xc],[y3,yc],[wozek3,zc])
view(60,30)


for t=0:0.1:100
    %move head around
    xc=10 + sin(t)
    yc=10 + cos(t)
    %compute new postions
    wozek1=zc+sqrt(r^2-(x1-xc)^2-(y1-yc)^2)
    wozek2=zc+sqrt(r^2-(x2-xc)^2-(y2-yc)^2)
    wozek3=zc+sqrt(r^2-(x3-xc)^2-(y3-yc)^2)
    %draw them
    set(ramie1,'XData',[x1,xc],'YData',[y1,yc],'ZData',[wozek1,zc])
    set(ramie2,'XData',[x2,xc],'YData',[y2,yc],'ZData',[wozek2,zc])
    set(ramie3,'XData',[x3,xc],'YData',[y3,yc],'ZData',[wozek3,zc])
    drawnow
    if (t>0) 
        krok1=round(200*(wozek1-stare1)) %compute step
        krok2=round(200*(wozek2-stare2))
        krok3=round(200*(wozek3-stare3))
        fprintf(s,'x %d y %d z %d t %d',[krok1 krok2 krok3 150]) %send steps with temp
        while (s.BytesAvailable == 0) %waitinf for the response
        end
        while (s.BytesAvailable>0)
        fscanf(s) %read temp
        end
    end
    stare1=wozek1 %previous positions
    stare2=wozek2
    stare3=wozek3
end
