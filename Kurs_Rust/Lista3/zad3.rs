struct Cipher {
    map1: String,
    map2: String
  }
  
impl Cipher {
    fn new(map1: &str, map2: &str) -> Cipher {
      Cipher { map1: map1.to_string(), map2: map2.to_string() }
    }
    
    fn encode(&self, string: &str) -> String {
      string.chars()
            .map(|c| match self.map1.chars().position(|c2| c2 == c) {
                None     => c.to_string(),
                Some(c)  => self.map2.chars()
                                     .nth(c)
                                     .unwrap()
                                     .to_string()
            })
            .collect()
    }
    
    fn decode(&self, string: &str) -> String {
        string.chars()
        .map(|c| match self.map2.chars().position(|c2| c2 == c) {
            None     => c.to_string(),
            Some(c)  => self.map1.chars()
                                 .nth(c)
                                 .unwrap()
                                 .to_string()
        })
        .collect()   
    }
}


fn main() {
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
      let map1 = "abcdefghijklmnopqrstuvwxyz";
      let map2 = "etaoinshrdlucmfwypvbgkjqxz";
      let cipher = Cipher::new(map1, map2);
      assert_eq!(cipher.encode("abc"), "eta");
      assert_eq!(cipher.encode("xyz"), "qxz");
      assert_eq!(cipher.decode("eirfg"), "aeiou");
      assert_eq!(cipher.decode("erlang"), "aikcfu");
    }

    #[test]
    fn test2() {
      let map1 = "dbcefsgpklzmoqrituhavwnxjy";
      let map2 = "poibnshtdlucxemfqwyavrgkjz";
      let cipher = Cipher::new(map1, map2);
      assert_eq!(cipher.encode("abc"), "aoi");
      assert_eq!(cipher.encode("xyz"), "kzu");
      assert_eq!(cipher.decode("iblen"), "celqf");
      assert_eq!(cipher.decode("pqure"), "dtzwq");
      assert_eq!(cipher.decode("bnlds"), "eflks");
      assert_eq!(cipher.encode("a.c"), "a.i");
      assert_eq!(cipher.decode("ib1l2e3n"), "ce1l2q3f");
    }

}
  
