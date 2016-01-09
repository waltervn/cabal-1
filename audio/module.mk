MODULE := audio

MODULE_OBJS := \
	adlib.o \
	audiodevice.o \
	audiostream.o \
	fmopl.o \
	mididrv.o \
	midiparser_qt.o \
	midiparser_smf.o \
	midiparser_xmidi.o \
	midiparser.o \
	midiplayer.o \
	miles_adlib.o \
	miles_mt32.o \
	mixer.o \
	mpu401.o \
	musicplugin.o \
	null.o \
	timestamp.o \
	decoders/3do.o \
	decoders/aac.o \
	decoders/adpcm.o \
	decoders/aiff.o \
	decoders/flac.o \
	decoders/iff_sound.o \
	decoders/mac_snd.o \
	decoders/mp3.o \
	decoders/qdm2.o \
	decoders/quicktime.o \
	decoders/raw.o \
	decoders/voc.o \
	decoders/vorbis.o \
	decoders/wave.o \
	decoders/xa.o \
	mods/infogrames.o \
	mods/maxtrax.o \
	mods/module.o \
	mods/protracker.o \
	mods/paula.o \
	mods/rjp1.o \
	mods/soundfx.o \
	mods/tfmx.o \
	softsynth/cms.o \
	softsynth/opl/dbopl.o \
	softsynth/opl/dosbox.o \
	softsynth/opl/mame.o \
	softsynth/fmtowns_pc98/towns_audio.o \
	softsynth/fmtowns_pc98/towns_euphony.o \
	softsynth/fmtowns_pc98/towns_midi.o \
	softsynth/fmtowns_pc98/towns_pc98_driver.o \
	softsynth/fmtowns_pc98/towns_pc98_fmsynth.o \
	softsynth/fmtowns_pc98/towns_pc98_plugins.o \
	softsynth/appleiigs.o \
	softsynth/fluidsynth.o \
	softsynth/mt32.o \
	softsynth/eas.o \
	softsynth/pcspk.o \
	softsynth/sid.o \
	softsynth/wave6581.o

ifdef USE_ALSA
MODULE_OBJS += \
	alsa_opl.o
endif

ifndef USE_ARM_SOUND_ASM
MODULE_OBJS += \
	rate.o
else
MODULE_OBJS += \
	rate_arm.o \
	rate_arm_asm.o
endif

# Include common rules
include $(srcdir)/rules.mk
