function []=global_asc_conv(filename)
% reads asc files, formats them like global_edf_conv does, and saves mat
% file. currntly no fixations and saccades. 
% Roy Amit, 2017


asc = read_eyelink_ascn(filename)
eval([filename(1:(end-4)) '.gazeRight.time=asc.dat(1,:)' ]);
eval([filename(1:(end-4)) '.gazeRight.x=asc.dat(2,:)' ]);
eval([filename(1:(end-4)) '.gazeRight.y=asc.dat(3,:)' ]);
eval([filename(1:(end-4)) '.gazeRight.pupil=asc.dat(4,:)' ]);
eval([filename(1:(end-4)) '.gazeLeft.time=asc.dat(1,:)' ]);
eval([filename(1:(end-4)) '.gazeLeft.x=asc.dat(5,:)' ]);
eval([filename(1:(end-4)) '.gazeLeft.y=asc.dat(6,:)' ]);
eval([filename(1:(end-4)) '.gazeLeft.pupil=asc.dat(7,:)' ]);


for i=1:length(asc.input)
    a(i).input=asc.input(i).value;
    a(i).time=asc.input(i).timestamp;
end
eval([filename(1:(end-4)) '.inputs=a' ]);

clear a 
for i=1:length(asc.msg)
    q=asc.msg{i};
    time=sscanf(q,'%*s%f');
    
    A=sscanf(q,'%*s%*f%s');
    MSG=char(A)';
    a(i).message=MSG;
    a(i).time=time;
end
eval([filename(1:(end-4)) '.messages=a' ])

clear a 
for i=1:length(asc.sbl)
    q=asc.sbl{i};
    sttime=sscanf(q,'%*s%*s%f');
     q=asc.ebl{i};
    edtime=sscanf(q,'%*s%*s%f');
    
    a.startTime(i)=sttime;
    a.endTime(i)=edtime;
end
eval([filename(1:(end-4)) '.blinks=a' ])


save(filename(1:(end-4)),filename(1:(end-4)))