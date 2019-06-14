import("stdfaust.lib");
decay  = hslider("decay", 3, 0.1, 13, 0.01);
reverb = _ <: re.zita_rev1_stereo(50,200,6000,decay*1.2,decay,48000.0) :> _;
process = _ + reverb*0.7;
