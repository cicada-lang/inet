+ diff diff-append "diff-list.inet"
+ sole "trivial.inet"

( TODO re-design syntax to remove the idea of (node) spread )

= one-two-soles
  (diff) spread $front sole cons front connect
  (diff) spread $front sole cons sole cons front connect
  diff-append

. one-two-soles

= two-two-soles
  (diff) spread $front sole cons sole cons front connect
  (diff) spread $front sole cons sole cons front connect
  diff-append

. two-two-soles