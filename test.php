2 function search($vect, $mat) {
  13   $result = array();
  14   foreach ($vect as $v) {
  15     $found = true;
  16     foreach ($mat as $sk => $sv) {
  17       if ($v[$sk] !== $sv) $found = false;
  18     } 
  19     if ($found) $result[] = $v;
  20   } 
  21   
  22   return $result;
  23 } 
