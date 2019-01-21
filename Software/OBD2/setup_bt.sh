#!/bin/bash

sudo service bluetooth restart

sudo sdptool add --channel=22 SP

sudo rfcomm listen /dev/rfcomm0 22