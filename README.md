reljmp
======

A simple module that can replace kernel functions on a live system. It follows
the kpropbe approach and replaces the first few bytes of the original (to be
replaced) function with a relative jump to the replacement function.

I don't have to tell you how dangerous this is and how easily things can blow
up in your face. If you don't believe me, you probably shouldn't try this :-)

The skel module in this repo is a simple example that replaces the kernel's
printk() function with our own version. It's based on a 2.6.38 kernel simply
because that's what was running on the system where I had to do this. If you
need this for a different kernel, you might want to check the kprobes code to
verify that the approach is still valid.
