import nzero nadd1 nadd "nat.fth"

define one nzero nadd1 end
define two one one nadd end
define three two one nadd end
define four two two nadd end

two two nadd
two two nadd
nadd
