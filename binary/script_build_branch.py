"""
Post-build script for PlatformIO.
Copies and renames the firmware binary to the binary/ directory.
Naming format: firmware_<env_name>_<git_branch>.bin
"""

import os
import shutil
import subprocess

Import("env")


def get_git_branch(project_dir):
    """Get the current git branch name."""
    try:
        result = subprocess.run(
            ["git", "rev-parse", "--abbrev-ref", "HEAD"],
            capture_output=True,
            text=True,
            check=True,
            cwd=project_dir,
        )
        branch = result.stdout.strip()
        # Sanitize branch name: replace / and other special chars with _
        branch = branch.replace("/", "_").replace("\\", "_").replace(" ", "_")
        return branch
    except (subprocess.CalledProcessError, FileNotFoundError):
        return "unknown-branch"


def copy_firmware(source, target, env):
    """Post-build action to copy and rename firmware binary."""
    firmware_path = str(target[0])
    
    # Only process .bin files
    if not firmware_path.endswith(".bin"):
        return
    
    project_dir = env.subst("$PROJECT_DIR")
    env_name = env.subst("$PIOENV")
    git_branch = get_git_branch(project_dir)
    
    # Build new filename
    new_filename = f"firmware_{env_name}_{git_branch}.bin"
    
    # Get binary directory (relative to project root)
    binary_dir = os.path.join(project_dir, "binary")
    dest_path = os.path.join(binary_dir, new_filename)
    
    # Ensure binary directory exists
    if not os.path.exists(binary_dir):
        os.makedirs(binary_dir)
    
    # Copy the firmware
    try:
        shutil.copy2(firmware_path, dest_path)
        print(f"\n{'='*60}")
        print(f"Firmware copied to: {dest_path}")
        print(f"Environment: {env_name}")
        print(f"Git Branch: {git_branch}")
        print(f"{'='*60}\n")
    except Exception as e:
        print(f"\nError copying firmware: {e}\n")


# Register the post-build action
env.AddPostAction("$BUILD_DIR/firmware.bin", copy_firmware)
