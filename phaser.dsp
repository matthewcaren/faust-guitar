import("stdfaust.lib");
speed  = hslider("speed", 0.5, 0, 10, 0.001);
// phaser2_mono(Notches,phase,width,frqmin,fratio,frqmax,speed,depth,fb,invert)
phaser = _ : pf.phaser2_mono(2, 0, 1000, 58, 5.86, 1000, speed, 1, .5, 0);
reverb = phaser <: re.zita_rev1_stereo(50,200,6000,2,3,48000.0) :> _;
process = phaser + reverb*0.5;
