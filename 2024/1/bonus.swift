import Foundation

func readFileContent(from fileName: String, at directoryPath: String) -> String {
    let fileManager = FileManager.default

    if fileManager.fileExists(atPath: directoryPath) {
        let directoryURL = URL(fileURLWithPath: directoryPath) 
        let fileURL = directoryURL.appendingPathComponent(fileName)
        do { 
            let fileContents = try String(contentsOf: fileURL, encoding: .utf8)
            return fileContents
        } catch {
            return "Error reading file: \(error)"
        }
    } else {
        return "Failed to find directory: \(directoryPath)"
    }
}

func splitContent(input: String) -> ([Int], [Int]) {
    let lines = input.split(separator: "\n")
    var left : [Int] = []
    var right : [Int] = [] 

    for line in lines {
        let numbers = line.split(separator: " ")
        if let leftNumber = Int(numbers[0]), let rightNumber = Int(numbers[1]) {
            left.append(leftNumber)
            right.append(rightNumber)
        }
    }
    return (left,right)
}

func findFirstOccurrence(of target: Int, in array: [Int]) -> Int? {
    var low: Int =  0
    var high: Int = array.count - 1
    var result: Int? = nil
    while low <= high {
        let mid = low + (high - low) / 2
        if array[mid] == target {
            result = mid
            high = mid - 1
        } else if array[mid] < target {
            low = mid + 1
        } else {
            high = mid - 1
        }
    }
    return result
}


func calcDistance( left: [Int] , right: [Int]) -> Int {
    var i: Int = 0
    let max : Int = left.count
    var result : Int = 0
    var counter = 0

    while i < max {
        counter = 0
        if let first = findFirstOccurrence( of: left[i], in : right) {
            while  right[first + counter] == left[i]{
                counter += 1
                if first + counter == right.count{
                    break
                }
            }
        }
        print(counter)
        result = result + (left[i] * counter)
        i += 1
    }
    return result
}

func main() {
    let fileName = "input"
    let fileManager = FileManager.default
    let currentDirectoryPath = fileManager.currentDirectoryPath
    var content : String = ""
    content = readFileContent(from: fileName, at: currentDirectoryPath)

    var (left, right) = splitContent( input:content )
    left = left.sorted()
    right = right.sorted()
    let result = calcDistance( left:left, right:right )
    print (result)
}

main()
