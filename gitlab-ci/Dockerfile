FROM registry.gitlab.homeserver.org/dist/ue5baseimage:0.2
USER ue4
WORKDIR /
RUN sudo chown -R ue4:ue4 /home/ue4

COPY Tetris.uproject /home/ue4/UnrealEngine/project/Tetris.uproject
COPY Source /home/ue4/UnrealEngine/project/Source
COPY Content /home/ue4/UnrealEngine/project/Content
COPY Config /home/ue4/UnrealEngine/project/Config

COPY gitlab-ci ci/
ENTRYPOINT ["python3","ci/build_project.py"]