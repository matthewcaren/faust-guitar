import("stdfaust.lib");
process = _ : ef.cubicnl_nodc(vslider("distortion",0.6,0,1,0.01),vslider("offset",0.4,0,1,0.01)):
	fi.lowpass(4,vslider("rolloff",2700,200,20000,1)):
	component("tubes.lib").T1_12AX7 : *(preamp):
	fi.lowpass(1,6531.0) : component("tubes.lib").T2_12AX7 : *(preamp):
	fi.lowpass(1,6531.0) : component("tubes.lib").T3_12AX7 : *(gain) with {
	preamp = vslider("Pregain",2,-20,20,0.1) : ba.db2linear;
	gain  = vslider("Gain", 0, -20.0, 20.0, 0.1) : ba.db2linear;
};