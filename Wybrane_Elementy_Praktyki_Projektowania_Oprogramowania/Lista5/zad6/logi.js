for(let i=0; i<10000; i++){
    let time = "01:23:45";
    let client_one = 10+Math.floor(Math.random() * 2);
    let client_two = 20+Math.floor(Math.random() * 2);
    let client_three = 30+Math.floor(Math.random() * 2);
    let client_four = 40+Math.floor(Math.random() * 2);
    let client = client_one.toString() + "." + client_two.toString() + "." + client_three.toString() + "." + client_four.toString();
    let rest =  "GET /TheApplication/WebResource.axd 200";
    console.log(time, client, rest);
}