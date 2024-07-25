import os

def setup_env():
    with open("ci/env","r") as fp:
        for line in fp.readlines():
            content = line.strip().split("=")
            os.environ[content[0]]=content[1]

def run_build():
    cmd =(
        "/home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh "\
        "BuildCookRun " \
        "-utf8output " \
        f"-platform={os.environ['PLATFORM']} " \
        f"-clientconfig={os.environ['CLIENT_CONFIG']} " \
        f"-serverconfig={os.environ['SERVER_CONFIG']} " \
        f"-project={os.environ['PROJECT_PATH']} " \
        "-noP4 -nodebuginfo -allmaps " \
        "-cook -build -stage -prereqs -pak -archive " \
        f"-archivedirectory={os.environ['ARCHIVE_DIR']}"
    )
    
    os.system(cmd)

if __name__ == "__main__":
    setup_env()
    run_build()
