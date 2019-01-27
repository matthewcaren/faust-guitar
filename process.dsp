import("stdfaust.lib");
octaver = _+ef.transpose(1500,600,-12);
distortion = ef.cubicnl(hslider("drive ", 0.2, 0, 1, 0.01),0);
flanger = pf.flanger_mono(32,hslider("flanger freq ", 10, 2, 32, 0.01),0,1,0,0);
tonestack = component("tonestacks.lib").bassman(t,m,l) 
	with {
		t = hslider("Treble ", 0.5, 0, 1, 0.01);
		m = hslider("Middle ", 0.5, 0, 1, 0.01);
		l = hslider("Bass ", 0.5, 0, 1, 0.01);
	};
amp = component("tubes.lib").T1_12AX7 : *(preamp):
	fi.lowpass(1,6531.0) : component("tubes.lib").T2_12AX7 *(preamp) :
	fi.lowpass(1,6531.0) : component("tubes.lib").T3_12AX7 *(gain)
	with {
		preamp = hslider("Pregain",-6,-20,20,0.1) : ba.db2linear : si.smoo;
		gain  = hslider("Gain", -6, -20.0, 20.0, 0.1) : ba.db2linear : si.smoo;
	};
process = octaver : distortion : flanger : tonestack : amp <: dm.zita_light;