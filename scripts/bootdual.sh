test -n ${BOOT_ORDER} || setenv BOOT_ORDER A B;
test -n ${BOOT_A_LEFT} || setenv BOOT_A_LEFT 3;
test -n ${BOOT_B_LEFT} || setenv BOOT_B_LEFT 3;

bootargs_A=\'rauc.slot=A\';
echo bootargs_A=${bootargs_A};

bootargs_B=\'rauc.slot=B\';
echo bootargs_B=${bootargs_B};

setenv bootargs_db;
for BOOT_SLOT in ${BOOT_ORDER}; do
  if test -n ${bootargs_db}; then
    echo bootargs_db:${bootargs_db};
  elif test x${BOOT_SLOT} = xA; then
    if test ${BOOT_A_LEFT} -gt 0; then
      echo Found valid slot A, ${BOOT_A_LEFT} attempts remaining;
      setexpr BOOT_A_LEFT ${BOOT_A_LEFT} - 1;
      setenv loadaddr_kernel ${kerneladdr_a};
      setenv bootargs_db ${bootargs_A};
    fi;
  elif test x${BOOT_SLOT} = xB; then
    if test ${BOOT_B_LEFT} -gt 0; then
      echo Found valid slot B, ${BOOT_B_LEFT} attempts remaining;
      setexpr BOOT_B_LEFT ${BOOT_B_LEFT} - 1;
      setenv loadaddr_kernel ${kerneladdr_b};
      setenv bootargs_db ${bootargs_B};
    fi;
  fi;
done;

if test -n ${bootargs_db}; then
  saveenv;
  echo bootargs_db:${bootargs_db};
  echo loadaddr_kernel:${loadaddr_kernel};
  echo BOOT_SLOT:${BOOT_SLOT} BOOT_A_LEFT:${BOOT_A_LEFT} BOOT_B_LEFT:${BOOT_B_LEFT};
else
  echo No valid slot found, resetting tries to 3;
  setenv BOOT_A_LEFT 3;
  setenv BOOT_B_LEFT 3;
  saveenv;
  re;
fi;

echo Loading kernel;
echo Starting kernel;
bootm ${loadaddr_kernel};
