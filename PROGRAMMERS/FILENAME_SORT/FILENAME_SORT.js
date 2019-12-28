const compare_function = (obj1, obj2) => {
  const head1_in_lo = obj1.head.toLowerCase();
  const head2_in_lo = obj2.head.toLowerCase();
  if (head1_in_lo.localeCompare(head2_in_lo) !== 0)
    return head1_in_lo > head2_in_lo ? 1 : -1;

  const num1 = parseInt(obj1.number);
  const num2 = parseInt(obj2.number);
  if (num1 == num2) return obj1.index - obj2.index;
  return num1 > num2 ? 1 : -1;
};

function solution(files) {
  const unsorted = files.map((file, index) => {
    const number_index = file.match("[0-9]").index;
    const head = file.substr(0, number_index);
    const body = file.substr(number_index);
    const tail_obj = body.match("[^0-9]");
    const tail_index =
      tail_obj == null ? 5 : tail_obj.index > 5 ? 5 : tail_obj.index;
    const number = tail_obj == null ? body : body.substr(0, tail_index);
    return {
      name: file,
      head,
      number,
      index
    };
  });

  const sorted = unsorted.sort(compare_function);

  const result = sorted.map(obj => obj.name);
  return result;
}

const inputs = [
  "img2.JPG",
  "img12.png",
  "img10.png",
  "img02.png",
  "img1.png",
  "IMG000001.GIF",
  "img0"
];

const inputs2 = [
  "B-50 Superfortress",
  "A-10 Thunderbolt II",
  "F-5 Freedom Fighter",
  "F-00005 Tomcat"
];
const inputs3 = ["F-15", "foo010bar020.zip", "fo010"];

const inputs4 = [
  "muzi asd9.txt",
  "MU ZI009.txt",
  "muzi09.txt",
  "mu zi13.TX",
  "Mu.zi012",
  "mu-zi1"
];
console.log(solution(inputs));
console.log("." > " ");
