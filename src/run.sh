#!/bin/bash
qemu-system-x86_64 -kernel kernel -serial stdio -m 8G -initrd $1
