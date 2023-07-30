#!/bin/bash -e

function jumpto
{
    label=$1
    cmd=$(sed -n "/$label:/{:a;n;p;ba};" $0 | grep -v ':$')
    eval "$cmd"
    exit
}

CONFIG_DIR=~/.LAC
LAC_DIR=/usr/bin
RESOURCE_DIR=/usr/share/lac
EXECUTABLE_DIR=$LAC_DIR
MUSIC_DIR=$RESOURCE_DIR/music
SOUNDS_DIR=$RESOURCE_DIR/sounds
MODELS_DIR=$RESOURCE_DIR/models
TEXTURES_DIR=$RESOURCE_DIR/textures

if [ -d "$LAC_DIR" ]; then
    jumpto skip2
fi
    echo $LAC_DIR does not exist. Creating it...
    mkdir $LAC_DIR
skip2:
if [ -d "$RESOURCE_DIR" ]; then
    jumpto skip3
fi
    echo $RESOURCE_DIR does not exist. Creating it...
    mkdir $RESOURCE_DIR
skip3:
if [ -d "$EXECUTABLE_DIR" ]; then
    jumpto skip6
fi
    echo $EXECUTABLE_DIR does not exist. Creating it...
    mkdir $EXECUTABLE_DIR
    jumpto skip7
skip6:
    echo Using EXISTING executable subdirectory $EXECUTABLE_DIR   
skip7:
    echo Copying main executable file...
    cp bin/Release/Lac09p15 $EXECUTABLE_DIR/lac
    chmod +x $EXECUTABLE_DIR/lac
    echo $RESOURCE_DIR will be used for resources. Copying icon there...
    cp lac.png $RESOURCE_DIR/lac.png
    chmod +r $RESOURCE_DIR/lac.png 
    echo Copying DefaultHeightMap.LAC into $RESOURCE_DIR
    cp DefaultHeightMap.LAC $RESOURCE_DIR/DefaultHeightMap.LAC
    chmod +r $RESOURCE_DIR/DefaultHeightMap.LAC
skip8:
if [ -d "$MUSIC_DIR" ]; then
    jumpto skip9
fi
    echo $MUSIC_DIR does not exist. Creating it...
    mkdir $MUSIC_DIR
    jumpto skip10
skip9:
    echo Using EXISTING music subdirectory $MUSIC_DIR
skip10:
    echo Copying music files into music subdirectory....
    cp bin/music/* $MUSIC_DIR
    chmod +r $MUSIC_DIR/*
skip11:
if [ -d "$SOUNDS_DIR" ]; then
    jumpto skip12
fi
    echo $SOUNDS_DIR does not exist. Creating it...
    mkdir $SOUNDS_DIR
    jumpto skip13
skip12:
    echo Using EXISTING sounds subdirectory $SOUNDS_DIR
skip13:
    echo Copying sound files into sounds subdirectory....
    cp bin/sounds/* $SOUNDS_DIR
    chmod +r $SOUNDS_DIR/*
skip14:
if [ -d "$MODELS_DIR" ]; then
    jumpto skip15
fi
    echo $MODELS_DIR does not exist. Creating it...
    mkdir $MODELS_DIR
    jumpto skip16
skip15:
    echo Using EXISTING models subdirectory $MODELS_DIR
skip16:
    echo Copying model files into models subdirectory....
    cp bin/models/* $MODELS_DIR
    chmod +r $MODELS_DIR/*
skip17:
if [ -d "$TEXTURES_DIR" ]; then
    jumpto skip18
fi
    echo $TEXTURES_DIR does not exist. Creating it...
    mkdir $TEXTURES_DIR
    jumpto skip19
skip18:
    echo Using EXISTING textures subdirectory $TEXTURES_DIR
skip19:
    echo Copying texture files into textures subdirectory....
    cp bin/textures/* $TEXTURES_DIR
    chmod +r $TEXTURES_DIR/*
echo
echo A fresh copy of LINUX AIR COMBAT has been installed.
echo
exit
