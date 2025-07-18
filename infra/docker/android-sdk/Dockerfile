# Copyright (c) 2024 Samsung Electronics Co., Ltd. All Rights Reserved
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FROM ubuntu:jammy

# Build tool
RUN apt-get update && apt-get -qqy install build-essential cmake scons git pkg-config

# Additonal tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive \
    apt-get -qqy install wget zip unzip python3 python3-pip python3-venv python3-dev hdf5-tools curl
RUN python3 -m pip install --upgrade pip
RUN python3 -m pip install numpy flatbuffers

# Install java for gradle and android sdk (and file for NDK internally used)
ARG OPENJDK_VERSION=11
RUN apt-get install -y openjdk-${OPENJDK_VERSION}-jdk file
ENV JAVA_HOME=/usr/lib/jvm/java-${OPENJDK_VERSION}-openjdk-amd64

# Setup user to match host user, and give superuser permissions
ARG USER_ID=1000
ARG GROUP_ID=${USER_ID}
RUN apt-get update && apt-get -qqy install sudo
RUN addgroup --gid ${GROUP_ID} ubuntu && adduser --disabled-password --gecos '' --uid ${USER_ID} --gid ${GROUP_ID} ubuntu && usermod -aG sudo ubuntu
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
RUN echo 'ubuntu ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

# Clean archives (to reduce image size)
RUN apt-get clean -y

# Create directory to install android tools and set user to the one we just created
RUN mkdir -p /opt/android-tools && chown -R ${USER_ID}:${GROUP_ID} /opt/android-tools
USER ${USER_ID}
WORKDIR /opt/android-tools

# download and install Gradle
# https://services.gradle.org/distributions/
ARG GRADLE_VERSION=7.6.4
ARG GRADLE_DIST=bin
RUN wget -q https://services.gradle.org/distributions/gradle-${GRADLE_VERSION}-${GRADLE_DIST}.zip && \
    unzip gradle*.zip && \
    ls -d */ | sed 's/\/*$//g' | xargs -I{} mv {} gradle && \
    rm gradle*.zip

# download and install Android SDK
# https://developer.android.com/studio#command-tools
ENV ANDROID_HOME=/opt/android-tools/android-sdk
RUN wget -q -O commandlinetools.zip https://dl.google.com/android/repository/commandlinetools-linux-6514223_latest.zip

# Unzip bootstrap cmdline-tools (old version) to tmp dir and install cmdline-tools (latest openjdk supporting version)
# accept the license agreements of the SDK components
ARG CMDTOOLS_VERSION=10.0
RUN unzip -d tmp commandlinetools.zip && rm commandlinetools.zip
RUN yes | tmp/tools/bin/sdkmanager --sdk_root=${ANDROID_HOME} --licenses > /dev/null
RUN tmp/tools/bin/sdkmanager --sdk_root=${ANDROID_HOME} "cmdline-tools;${CMDTOOLS_VERSION}"
RUN rm -rf tmp

# Install android ndk and tools (other packages will be installed by gradle build)
ARG NDK_VERSION=26.3.11579264
RUN ${ANDROID_HOME}/cmdline-tools/${CMDTOOLS_VERSION}/bin/sdkmanager --sdk_root=${ANDROID_HOME} "ndk;${NDK_VERSION}"
RUN ${ANDROID_HOME}/cmdline-tools/${CMDTOOLS_VERSION}/bin/sdkmanager --sdk_root=${ANDROID_HOME} "platform-tools"

# Env variable for android build (ndk, gradle)
ENV NDK_DIR=${ANDROID_HOME}/ndk/${NDK_VERSION}
ENV GRADLE_HOME=/opt/android-tools/gradle
ENV PATH=${PATH}:${GRADLE_HOME}/bin:${ANDROID_HOME}/cmdline-tools/${CMDTOOLS_VERSION}/bin:${ANDROID_HOME}/tools:${ANDROID_HOME}/tools/bin:${ANDROID_HOME}/platform-tools

# setup adb server
EXPOSE 5037

WORKDIR /home/ubuntu
